#include "glwidget.h"

GLfloat triangleVerts[] = {
    -1.0,  -1.0, 0.0,
     -1.0,  1.0, 0.0,
    1.0, -1.0, 0.0,
    1.0, 1.0, 0.0
};


GLWidget::GLWidget(QWidget * parent):elapsed(0)
{
    constexpr auto FPS = 60.0;

    timer = new QTimer(this);
    openGLInitializationTime = std::chrono::high_resolution_clock::now();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerRedraw()));
    timer->start(1000/FPS);

}
GLWidget::~GLWidget()
{
    makeCurrent();
    delete m_program;
    delete m_vbo;
    delete m_vao;
    delete timer;
}
void GLWidget::initializeGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    m_program = new QOpenGLShaderProgram;


    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vCode);
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, fFile);
    m_program->link();


    delete m_vao;
    m_vao = new QOpenGLVertexArrayObject;
    if (m_vao->create())
        m_vao->bind();

    m_program->bind();
    delete m_vbo;
    m_vbo = new QOpenGLBuffer;
    m_vbo->create();
    m_vbo->bind();


    m_vbo->allocate(triangleVerts , sizeof(triangleVerts));
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);

    m_vbo->release();


}
void GLWidget::paintGL()
{
    QOpenGLExtraFunctions *f = QOpenGLContext::currentContext()->extraFunctions();

    f->glClearColor(0, 0, 0, 1);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_program->bind();
    f->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

}
void GLWidget::resizeGL(int width, int height)
{

}


void GLWidget::onTimerRedraw()
{
    makeCurrent();
    QOpenGLExtraFunctions *f = QOpenGLContext::currentContext()->extraFunctions();
    //f->glClearColor(0, 0, 0, 1);
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now() - openGLInitializationTime);
            elapsed = duration.count() / 1000.0f;
    f->glUniform1f(f->glGetUniformLocation(m_program->programId(), "iTime"), elapsed);
    qDebug() << "Elapsed time is " << elapsed;
    update();
}

void GLWidget::shaderRecompile()
{
    delete m_program;
    m_program = new QOpenGLShaderProgram;
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vCode);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, currentFShader);
    m_program->link();
}

