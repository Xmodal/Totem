#include "ofApp.h"

extern double drand48(void);
extern void srand48(long seedval);

int iterate;
int height = 360;
double lll,rrr;
double resr[8],resl[8];


#define N 1000
#define Ntime 800
#define MAXPOINTS 100      /*  */
int pointnum = 0;          /*  */
int rubberband = 0;        /*  */
int itime=0;
int nnnn;        /* rule number */
int TIME=  240000;
int x[N],xx[N];
int bbbbb[N][Ntime];
int    Nsize=800;
double   color[N];
int  w0,w1,w2,w3,w4,w5,w6,w7,w8;

void spacetime_initialize(int *x)
{
    int k,j;
    
    for(k=0;k<N;k++){
        for(j=0;j<Ntime;j++)
            bbbbb[k][j] = 0;
    }
}

void spacetime(int *x)
{
    int i,k,j;
    
    for(k=0;k<Nsize;k++){
        for(j=0;j<(height-1);j++){
            bbbbb[k][j] = bbbbb[k][j+1];
        }
    }
    for(k=0;k<Nsize;k++)
        bbbbb[k][height-1] = x[k];
    
}

int rule(int x,int y,int z)
{
    if((x==0)&&(y==0)&&(z==0))
        return(w0);
    if((x==0)&&(y==0)&&(z==1))
        return(w1);
    if((x==0)&&(y==1)&&(z==0))
        return(w2);
    if((x==0)&&(y==1)&&(z==1))
        return(w3);
    if((x==1)&&(y==0)&&(z==0))
        return(w4);
    if((x==1)&&(y==0)&&(z==1))
        return(w5);
    if((x==1)&&(y==1)&&(z==0))
        return(w6);
    if((x==1)&&(y==1)&&(z==1))
        return(w7);
    
}
void  rule_initialize(int nnnn)
{
    w0  = nnnn- 2*(nnnn/2);
    nnnn = nnnn/2;
    w1  = nnnn- 2*(nnnn/2);
    nnnn = nnnn/2;
    w2  = nnnn- 2*(nnnn/2);
    nnnn = nnnn/2;
    w3  = nnnn- 2*(nnnn/2);
    nnnn = nnnn/2;
    w4  = nnnn- 2*(nnnn/2);
    nnnn = nnnn/2;
    w5  = nnnn- 2*(nnnn/2);
    nnnn = nnnn/2;
    w6  = nnnn- 2*(nnnn/2);
    nnnn = nnnn/2;
    w7  = nnnn- 2*(nnnn/2);
    nnnn = nnnn/2;
}
/*--------------------------------------------------------------
 sound production
 -------------------------------------------------------------*/
void sound_production(int *x,int nnnn)
{
    double ddd;
    
    int i,j,k;
    int Nbegin=10,Nend=18;
    
    
    
    //    printf("itime =  %d\n",itime);
    int counter = 0;
    switch(nnnn){
        case 110:
            for(k=Nbegin;k<Nend;k++){
                lll=0;
                ddd=2;
                for(j=k;j<(Nsize/2+1);j++){
                    lll += x[Nsize/2-j-1];
                }
                
                lll = 2.*lll/(Nsize/2+1) -1.0;
                
                rrr=0;
                ddd=2;
                for(j=k;j<Nsize/2;j++){
                    rrr += x[Nsize/2+j];
                }
                
                rrr = 2.*rrr/(Nsize/2+1) -1.0;
                
                
                
                for(j=0;j<iterate;j++)
                    printf("%6.5lf %6.5lf\t",lll,rrr);
                resr[counter] = rrr;
                resl[counter] = lll;
                counter += 1;
                // printf("%32.31lf %32.31lf\n",lll,rrr);
            }
            printf("\n");
            
            
            
            break;
        default:
            
            int counter = 0;
            for(k=Nbegin;k<Nend;k++){
                
                //                printf("%6.5lf",k);
                lll=0;
                ddd=2;
                for(j=k;j<(Nsize/2+1);j++){
                    lll += x[Nsize/2-j]/ddd;
                    ddd *= 2;
                }
                
                lll = 2*lll -1;
                
                rrr=0;
                ddd=2;
                for(j=k;j<(Nsize/2-1);j++){
                    rrr += x[Nsize/2+j+1]/ddd;
                    ddd *= 2;
                }
                
                rrr = 2.*rrr -1.;
                
                
                
                
                //
                for(j=0;j<iterate;j++)
                    printf("%6.5lf %6.5lf\t",lll,rrr);
                resr[counter] = rrr;
                resl[counter] = lll;
                counter += 1;
                
                
                //                 printf("%32.31lf %32.31lf\t",lll,rrr);
                
                
                
                
                
                
            }
            printf("\n");
            
            break;
    }
    
}

/*---------------------------------------
 main dynamics controling module
 
 
 ----------------------------*/
void dynamics(void){
    double t;
    int i;
    
    itime++;
    for(i=0;i<Nsize;i++){
        
        if((i>0)&&(i<(Nsize-1)))
            xx[i] = rule(x[i-1], x[i], x[i+1]);
        
        if(i==0)
            xx[i] = rule(x[Nsize-1], x[i], x[i+1]);
        
        if(i==(Nsize-1))
            xx[i] = rule(x[Nsize-2], x[i], x[0]);
    }
    
    sound_production(x,nnnn);   /* making sound from the CA pattern */
    
    for(i=0;i<Nsize;i++)
        x[i] = xx[i];
    
}



void billiard(void){
    int i,k,j;
    
    
    spacetime(x);    /*   data transfer from x() to bbbbb() for drawing */
    
    glPointSize(5);
    glBegin( GL_POINTS );
    
    for(i=0;i<Nsize;i++){
        for(j=0;j<height;j++){
            if(bbbbb[i][j] == 1)
                //                ofSetColor(255, 255, 255);
                glColor3d(1,1,1);
            else
                //                ofSetColor(0, 0, 0);
                glColor3d(0,0,0);
            //            ofDrawRectangle(i, height-j, 5, 5);
            glVertex2d(i,height-j);
        }
    }
    glEnd();
    
}



//--------------------------------------------------------------
void ofApp::setup(){
    
    //    ofxSubscribeOsc(12047, "/oc/rulecntl", rulecntl);
    //    ofxSubscribeOsc(12047, "/oc/framerate", framerate);
    
    ofSetWindowShape(9, 360);
    iseed = 3056;
    nnnn = rulecntl;
    iflag = 1;
    TIME = 100000;
    iterate = 1;
    Nsize = 800;
    
    mainOutputSyphonServer.setName("OF_syphon");
    mClient.setup();
    
    //using Syphon app Simple Server, found at http://syphon.v002.info/
    //mClient.set("","Simple Server");
    
    ofSetBackgroundColor(0, 0, 0);
    ofSetFrameRate(framerate);
    
    sender.setup("192.168.100.11", 6448);
    
    
    srand48(iseed);
    rule_initialize(nnnn);
    
    if(iflag==0){
        for(i=0;i<Nsize;i++){
            if(drand48()>0.5)
                x[i] = 0;
            else
                x[i] = 1;
        }
    }
    
    if(iflag==1){
        for(i=0;i<Nsize;i++)
            x[i] = 0;
        x[Nsize/2] = 1;
    }
    
    if(iflag==2){
        for(i=0;i<Nsize;i++){
            if(drand48()>0.5)
                x[i] = 0;
            else
                x[i] = 1;
        }
    }
    
    
    spacetime_initialize(x);
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    nnnn = rulecntl;
    rule_initialize(nnnn);
    ofSetFrameRate(framerate);
    
    
    dynamics();
    
    ofxOscMessage msg;
    msg.setAddress("/oc");
    
    //    msg.addFloatArg(lll);
    //    msg.addFloatArg(rrr);
    for (int i=0; i<18; i++) {
        msg.addFloatArg(resr[i]);
        msg.addFloatArg(resl[i]);
    }
    
    sender.sendMessage(msg);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    billiard();
    
    //Syphon
    mClient.draw(9,360);
    mainOutputSyphonServer.publishScreen();
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
    if (key == 'r')
    {
        
        rule_initialize(30);
        
        if(iflag==0){
            for(i=0;i<Nsize;i++){
                if(drand48()>0.5)
                    x[i] = 0;
                else
                    x[i] = 1;
            }
        }
        
        if(iflag==1){
            for(i=0;i<Nsize;i++)
                x[i] = 0;
            x[Nsize/2] = 1;
        }
        
        if(iflag==2){
            for(i=0;i<Nsize;i++){
                if(drand48()>0.5)
                    x[i] = 0;
                else
                    x[i] = 1;
            }
        }
        
        
        spacetime_initialize(x);
        
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

