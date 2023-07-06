#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./myGLUT.h"



void lpdbCenterCalc(PDB* pdb){

  float sumx=0;
  float sumy=0;
  float sumz=0;
  
  pdb->current=pdb->top;
  while(pdb->current->nextAtom!=NULL){
    sumx += pdb->current->atom.x;
    sumy += pdb->current->atom.y;
    sumz += pdb->current->atom.z;

    pdb->current=pdb->current->nextAtom;
  }
  
  pdb->Center.x = sumx/pdb->numAtom;
  pdb->Center.y = sumy/pdb->numAtom;
  pdb->Center.z = sumz/pdb->numAtom;
}
