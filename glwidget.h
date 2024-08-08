#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLExtraFunctions>
#include <QTimer>
#include <iostream>
#include <QDebug>
#include <QTime>
#include <chrono>
#include <filesystem>




class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget * parent = 0);
    ~GLWidget();

void initializeGL() override;
void paintGL() override;
void resizeGL(int width, int height) override;
void shaderRecompile();

QTimer *timer;
GLfloat elapsed;
QString fFile = ".\\test1.fs";
QString currentFShader;

public slots:
void onTimerRedraw();

private:
QOpenGLShaderProgram *m_program = nullptr;
QOpenGLBuffer *m_vbo = nullptr;
QOpenGLVertexArrayObject *m_vao = nullptr;

std::chrono::high_resolution_clock::time_point openGLInitializationTime {};

const QString vCode =
        "#version 330 core\n"
        "layout(location = 0) in vec3 inPosition;\n"
        "out vec3 pos;\n"
        "void main(){\n"
        "pos = inPosition;\n"
        "gl_Position = vec4(inPosition, 1.0);}\n";

};

#endif // GLWIDGET_H
