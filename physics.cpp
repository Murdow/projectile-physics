#include <GL/glut.h>
#include <stdlib.h>
#include<math.h>

// prototipos das funcoes
void init(void);
void display(void);//Cria o quadrado
void keyboard(unsigned char key, int x, int y);
void Timer(int value); //Loop de atualizaçao das posiçes do cubo
void setMovement();//Converte angulo....Calcula movimento em X e Y
int positionX = 0, positionY = 0;
int gravidade = 10;
float time = 0;
float pi = 3.1415;
int ang;
int velocidadeInicial;
float y = 0;
float x = 0;
float rad = 0;
float vox = 0;
float voy = 0;
bool loop = true;

// funcao principal
int main(int argc, char** argv){
  glutInit(&argc, argv);                              // inicializa o glut
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);           // especifica o uso de cores e buffers
  glutInitWindowSize (800, 600);                          // especifica as dimensoes da janela
  glutInitWindowPosition (100, 100);                      // especifica aonde a janela aparece na tela
  glutCreateWindow ("Lançamento De Projetil");              // cria a janela
  init();
  
  velocidadeInicial= atoi(argv[1]); //Recebe o valor por linha de comando
  ang= atoi(argv[2]);
  
  setMovement();  
  glutDisplayFunc(display);                               // funcao que sera redesenhada pelo GLUT
  glutKeyboardFunc(keyboard);                             // funcoes de teclado  
  glutMainLoop();                                         // mostra todas as janelas criadas
  return 0;
}

// definicao de cada funcao

void init(){
  glClearColor(0.0, 0.0, 0.0, 1.0);    // cor de fundo
  glOrtho (0, 256, 0, 256, -1 ,1);     // modo de projecao ortogonal
} 

void display(){
  int i;
  glClear(GL_COLOR_BUFFER_BIT);               // limpa a janela
  glColor3f (1.0, 0.0, 0.0);                  // cor do quadrado
  //cria o quadrado                
  glBegin(GL_QUADS);
          glVertex2i(positionX,positionY + 5);
          glVertex2i(positionX,positionY);    // coordenadas quadrado
          glVertex2i(positionX + 5,positionY);
          glVertex2i(positionX + 5,positionY + 5); 
  glEnd();
  glFlush();
}

void setMovement()
{
     rad = ang * pi / 180;
     vox = velocidadeInicial * cos(rad);
     voy = velocidadeInicial * sin(rad);
}

void keyboard(unsigned char key, int x, int y){
  if(key == 27)
         exit(0);  
  else if(key == 'a')
  {      
       Timer(10);       
  }
}
void Timer(int value)
{     
     if(loop == true)
     {
       time += 0.2;
       x = vox * time;
       y = voy * time - 0.5 * gravidade * (time * time);
       positionX = (int)x;       
       positionY = 0 + (int)y;
       if(positionY <= 0)
       {
              loop = false;
              positionY = 0;              
       }      
       display();//Redesenha o quadrado nas posiçoes atualizadas
       glutTimerFunc(80,Timer, 1);//Chama d novo a funçao Timer a cada 80 milesec....       
     }     
}
