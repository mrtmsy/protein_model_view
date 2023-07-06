#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./myGLUT.h"

void lpdbSizeCalc(PDB* pdb){

  float maxsize=0;
  float size=0;
  
  pdb->current=pdb->top;
  while(pdb->current->nextAtom!=NULL){
    size=sqrt((pdb->current->atom.x - pdb->Center.x)*(pdb->current->atom.x - pdb->Center.x)+
              (pdb->current->atom.y - pdb->Center.y)*(pdb->current->atom.y - pdb->Center.y)+
              (pdb->current->atom.z - pdb->Center.z)*(pdb->current->atom.z - pdb->Center.z));
    if(maxsize < size){
      maxsize = size;
    }
    pdb->current=pdb->current->nextAtom;
  }
  
  pdb->maxRadius=maxsize;
  
}
