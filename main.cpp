
 #define PI 3.14159265

#include "stlReader.h"
#include "predictor.h"


void pingArray(float * A, int row, int col){
  if(row * col > 100) {
    printf("error huge array print\n");
    return;
  }
  for(int i = 0; i < row; i++){
    for(int j = 0 ; j < col; j++)
    std::cout <<A[i*col + j] << " ~ " ;
    std::cout <<std::endl;
  }
 std::cout <<std::endl;
}

void opt(int name){
Optimizer optimizer;
StlReader reader;
 std::string basename = "/home/accts/jcb97/proj/stls/";
printf("optimizing %d\n", name);
reader.openFile(basename + "data/" + std::to_string(name) +".stl", false);
  reader.getStats();
  reader.restReading();
rot bestrot;
optimizer.bestRotate(&reader, &bestrot);
reader.setRotation(bestrot);
reader.setDown(false);
reader.saveObject(basename +"opt/" + std::to_string(name) +".stl");

}


int main(void)
{
  //srand(11235813);
  std::cout << "Staring up World!" << std::endl;
  StlReader reader;
   std::string basename = "/home/accts/jcb97/proj/stls/";
/*

  reader.openFile(basename + "data/2.stl", false);
  reader.getStats();
  reader.restReading();
 Objstats stats;
  FeatureFinder finder; 
  finder.getFeatures( &stats, &reader);
   reader.restReading();
*/
for(int i =16; i < 21; i++)
  opt (i);

  
 //Predictor guesser;
 // guesser.learnFrom("./data");
 // guesser.read("currentModel");
  //int buildtime =  guesser.predict("/home/accts/jcb97/proj/stls/data/9.stl");
  //std::cout << "\n got :" << buildtime << " to print 1"<< std::endl;
 // guesser.store("currentModel");
 //double score = guesser.test("./data");
 //std::cout <<" guesser r ^2 is:" << score << std::endl;
   
  //Predictor secondguesser;
  //secondguesser.read("currentModel");
  //score = secondguesser.test("./data");
  //std::cout <<" secondguesser got" << score << std::endl;
/*  
   float spin [3];
 //   int dim[3];
 //  dim[0] =300;
 // dim[1] = 300;
 // dim[2] = 300;
 
  for(int i = 42 ; i <62; i++){
    StlReader reader;
    std::string curname = basename+ std::to_string(i) +".stl";
    reader.openFile(curname, false);
    std::cout << curname << std::endl;
    for(int rot = 0; rot < 4; rot ++){
      for(int j = 0; j <3; j++ )
      {
        if(rot != 0) spin[j] = rand() * PI;
        else  spin[j] = 0;
      }
       reader.setRotation(spin);
      reader.getStats();
      reader.restReading();
 
     //reader.shrinkToFit(dim, false );
          reader.restReading();
      reader.setDown(false);
          reader.restReading();
      std::string outname = basename + "data/" + std::to_string(i*3 + rot)+".stl";
      reader.saveObject(outname);

      //pingArray(reader.transform.trans, 3,1);
       //   std::cout <<  std::endl;
      reader.clear();
    }
  }*/
 /*
  reader.getStats();
  reader.stats.print();
  reader.restReading();
  Objstats stats;
  FeatureFinder finder;
  finder.getFeatures( &stats, &reader);
   reader.restReading();


   float spin[3];
   spin[0] = 0.0;
    spin[1] = PI/2;
     spin[2] = PI/2;
   reader.setRotation(spin);
  reader.restReading();
   reader.getStats();
  reader.restReading();
 reader.stats.print();
 int dim[3];
 dim[0] =300;
 dim[1] = 300;
 dim[2] = 300;
 reader.shrinkToFit(dim,true );
 reader.setDown(false);
 reader.restReading();
    reader.getStats();
  

 reader.stats.print();
  reader.restReading();



  
  reader.restReading();
 reader.saveObject("/home/accts/jcb97/proj/stls/Teapotspin.stl");
std::cout << " -------------------------------"<< std::endl;
StlReader modreader;
modreader.openFile("/home/accts/jcb97/proj/stls/Teapotspin.stl", false);
 reader.restReading();
modreader.getStats();
modreader.stats.print();
*/
  return 0;
}