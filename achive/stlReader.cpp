#include <limits>
#include "stlReader.h"
#include <cstring>
#include <iostream>

void  StlReader ::  hello(void){
		std::cout << "Hello i'm a reader World!" << std::endl;
	} 

int StlReader :: openFile (std::string newname, bool overwrite){
	if(source.is_open()) return -1;
	source.open(newname, std::ios::in | std::ios::binary); 
	if(!source.is_open()) {
		std::cout << "could not open "<< newname << std::endl;
		return -2;
	}
	char front[8];
	 source.read(front, 8);
	 std::cout << front << std::endl;


	if(strcmp(front, "solid") == 0){
		std::cout << "not binary" << std::endl;
		isbinary = false;
		char firstline[256];
		source.getline(firstline, 256);
	}else{
		
		isbinary = true;
		char header [ 72];
		source.read(header, 72);
		std::cout << header << std::endl;
			if(source.fail())std::cout << "3 in failing failing" << std::endl;
		uint32_t temp = 0;
		source.read((char *) &temp, sizeof(temp));
		std::cout << "got value" <<temp << std::endl;
		stats.numbsurface = (uint32_t) temp; 
	}
	open = true;
	
	
	std::cout << "read done numbsurface "<< stats.numbsurface  << std::endl;
	return 0;
}


int StlReader :: getstats (void){
	//read through surfaces 
	float max = std::numeric_limits<float>::max()/10 ;
	for(int i =0; i < 3; i++){
		this->stats.extrema[2*i] = (float)   max ;
		this->stats.extrema[2*i +1] = (float) -1 * max ;
	//	std::cout << "extrema i is "<< this->stats.extrema[2*i +1]  << std::endl;
	}
	//this->stats.print();
	if(this->isbinary){
	

		float in[4][3];// norm[3], v1[3], v2[3], v3[3];
		char waste[2];
		float cur[2]; // min max
		for( int surface = 0; surface < (int) this->stats.numbsurface; surface++){
		
		//	surface = surface + 1;
	
			for(int vert= 0; vert< 4; vert++)
				source.read((char *) in[vert], sizeof(float) *3);
			source.read(waste, 2);
			for(int i =0 ; i < 3 ; i++)
				this->stats.avenorm[i] += in[0][i];
			for(int j = 0; j< 3 ; j++){
				if(in[1][j] <= in[2][j]) {
					cur[0] = in[1][j];
					cur[1] = in[2][j];
				}
				else{
					cur[0] = in[2][j];
					cur[1] = in[1][j];
				}
				if(in[3][j] > cur[1]) cur[1] = in[3][j];
				else if(in[3][j] < cur[0]) cur[0] = in[3][j];
				if(cur[0] < this->stats.extrema[2*j]) this->stats.extrema[2*j] =cur[0];
				if(cur[1] > this->stats.extrema[2*j + 1]) this->stats.extrema[2*j +1] =cur[1];
			
			}
		
 
		}
		for ( int i = 0; i < 3 ; i++)
			this->stats.avenorm[i] /= this->stats.numbsurface;
		//std::cout << this->stats.numbsurface  << std::endl;
	}
	return -1;
}


int StlReader :: setRotation (float spin[3]){
	std::cout << "setRotation not implimented !" << std::endl;
	return -1;
}
void StlStats:: print(void){
	std::cout << " numbsurface "; 
	std::cout << this->numbsurface << std::endl;
	std::cout << "x: "<< this->extrema[0]<< " -- "<< this->extrema[1] ;
	std::cout << "  y: "<< this->extrema[2]<< " -- "<< this->extrema[3];
	std::cout << "  z: "<< this->extrema[4]<< " -- "<< this->extrema[5] <<std::endl;
	std::cout << " avenorm " << this->avenorm[0] << " -- " << this->avenorm[1];
	std::cout << " -- " << this->avenorm[2] << std::endl;
}

int StlReader :: getsurface(sur * out){
	sur first;
	char waste[2];
	if(!this->open){
		std::cout << "cant read from closed reader" << std::endl;
		return -1;
	}

	for(int vert= 0; vert< 4; vert++)
			source.read((char *)  first[vert], sizeof(float) *3);
		source.read(waste, 2);

	if(this->transform.rotate){
		sur newrotation;
	}
	for(int i = 0 ; i < 4; i++)
		for(int j = 0 ; j < 3; j++)
			(*out) [i][j] = first[i][j];
	return 0;
}

Objstats StlReader :: getfeatures(void){
	Objstats mystats;
	float cross[3];
	float total = 0;
	float partial = 0;
	sur cur;
	for(uint32_t i = 0; i < this->stats.numbsurface; i++){
		this->getsurface(&cur);
		
		//volume = abs (a dot (b cross c)) /6 x sign 
		cross[0] = cur[2][1]*cur[3][2]-cur[2][2]*cur[3][1];
 		cross[1] = cur[2][2]*cur[3][0]-cur[2][0]*cur[3][2];
  		cross[2] = cur[2][0]*cur[3][1]-cur[2][1]*cur[3][0];
	
  		partial = cross[0] * cur[1][0] + cross[1] * cur[1][1] + cross[2] * cur[1][2];

  		partial = abs(partial) / 6.0;

  		float normsum = 0;
  		for( int j = 0; j < 3; j++)
  			normsum += cur[0][i];
  		//see if dot product of surface normal is positive
  		if(normsum < 0) {
  			//normal facing away add
  			total += partial;
  		}else total -= partial;

	}
	mystats.volume = total;
	std::cout << "total was:"<< total  << std::endl;
	return mystats;
}