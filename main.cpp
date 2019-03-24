/* Feito por: Carlos Henrique
/* Exemplo de um braço robotico com opengl
/* Projeto desenvolvido no ambiente linux - Manjaro Linux - x64 utilizando OpenGL
*/

#include <GL/glut.h>
#include <stdlib.h>

// angulo inicial dos objetos
static int angulo_braco = 0, angulo_ante_braco = 0, angulo_dedo1 = 0, angulo_dedo2 = 0;

/*
    Função que desenha os objetos
    cada vez que o angulo de algum objeto é alterado, ela é chamada novamente e atualiza a tela
*/
void DesenhaBraco()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // cria uma cópia da matrix para fazer as alterações
    glPushMatrix();

    /* criando o braço */
    // por ser o primeiro objeto não é necessário usar o glTranslatef(). pelo menos neste exemplo
    // rotaciona o braço conforme o valor do angulo definido na variável angulo_braço
    glRotatef((GLfloat) angulo_braco, 0,0,1);
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.5, 0);
        glVertex2f(-0.5, 3);
        glVertex2f(0.5, 3);
        glVertex2f(0.5, 0);
    glEnd();

    /* criando o ante-braço */
    // posiciona o ante-braço 3 pontos acima da origem
    glTranslatef(0, 3, 0);
    // rotaciona o ante-braço conforme o valor do angulo definido
    glRotatef((GLfloat) angulo_ante_braco, 0, 0, 1);
    glColor3f(1,1,0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.5, 0);
        glVertex2f(-0.5, 3);
        glVertex2f(0.5, 3);
        glVertex2f(0.5, 0);
    glEnd();

    /*
        como os dedos estão lado a lado e são independentes entre si,
        é necesário fazer um glPushMatrix para cada um deles dentro do glPushMatrix() anterior
     */
    // criando o dedo esquerdo
    glPushMatrix();
        glColor3f(0,1,0);
        // posiciona 3 pontos acima do ante-braço
        glTranslatef(0, 3, 0);
        // rotaciona o objeto conforme o angulo definido
        glRotatef((GLfloat) angulo_dedo1, 0, 0, 1);
        glBegin(GL_POLYGON);
            glVertex2f(-0.5, 0);
            glVertex2f(-0.5, 2);
            glVertex2f(-0.25, 2);
            glVertex2f(-0.25, 0);
        glEnd();
    glPopMatrix();

    // faz a mesma coisa do que o dedo esquerdo só que mais pra direita
    // criando o dedo direito
    glPushMatrix();
        glColor3f(0,1,0);
        glTranslatef(0, 3, 0);
        glRotatef((GLfloat) angulo_dedo2, 0, 0, 1);
        glBegin(GL_POLYGON);
            glVertex2f(0.5, 0);
            glVertex2f(0.5, 2);
            glVertex2f(0.25, 2);
            glVertex2f(0.25, 0);
        glEnd();
    glPopMatrix();

    // popMatrix() retorna a matrix atualizada pra matrix original
    glPopMatrix();
    glFlush();
}

/*
    Função responsável por ler as teclas e alterar o angulo do objeto
    conforme a tecla selecionada
*/
void LeTeclado(unsigned char tecla, int x, int y)
{
    switch (tecla)
    {
    case 'q': // movimenta o braço
        // incrementa em 2 o angulo se não estiver no limite
        if(angulo_braco <= 120) angulo_braco = angulo_braco + 2;
        glutPostRedisplay();
        break;
    case 'w':
        // decrementa em 2 o angulo se não estiver no limite
        if(angulo_braco >= -120) angulo_braco = angulo_braco - 2;
        glutPostRedisplay();
        break;

    case 'a': // movimenta o ante braco
        if(angulo_ante_braco <= 120) angulo_ante_braco = angulo_ante_braco + 2;
        glutPostRedisplay();
        break;
    case 's':
        if(angulo_ante_braco >= -120) angulo_ante_braco = angulo_ante_braco - 2;
        glutPostRedisplay();
        break;


    // moviementando os dedos
    case 'e': // movimenta o dedo 1
        if(angulo_dedo1 <= 20) angulo_dedo1 = angulo_dedo1 + 2;
        glutPostRedisplay();
        break;
    case 'r':
        if(angulo_dedo1 >= -10) angulo_dedo1 = angulo_dedo1 - 2;
        glutPostRedisplay();
        break;

    case 'd': // movimenta o dedo 2
        if(angulo_dedo2 <= 10) angulo_dedo2 = angulo_dedo2 + 2;
        glutPostRedisplay();
        break;
    case 'f':
        if(angulo_dedo2 >= -20) angulo_dedo2 = angulo_dedo2 - 2;
        glutPostRedisplay();
        break;
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(320,150);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutCreateWindow("Mechanical Arm");

    glutDisplayFunc(DesenhaBraco);
    glutKeyboardFunc(LeTeclado);
    glClearColor(0,0.5,0.5,1);
    glutMainLoop();

    return 0;
}
