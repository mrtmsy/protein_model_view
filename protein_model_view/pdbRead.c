#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "./myGLUT.h"

int pdbRead(FILE* fpt, PDB *pdb){

  char str[256];
  
  pdb->numAtom=0;
  pdb->numCA=0;
  pdb->current=(recordPDB*)malloc(sizeof(recordPDB));
  pdb->currentCA=(recordPDB*)malloc(sizeof(recordPDB));
  pdb->top=pdb->current;
  pdb->topCA=pdb->currentCA;
  
  while(fgets(str,256,fpt)!=NULL){
    if(strstr(str,"ATOM  ")!=NULL){
      pdb->numAtom++;
      
      pdb->current->nextAtom=(recordPDB*)malloc(sizeof(recordPDB));
      
      pdb->current->atom.x=atof(&str[30]);
      pdb->current->atom.y=atof(&str[38]);
      pdb->current->atom.z=atof(&str[46]);
      strncpy(pdb->current->atom.resName,str+17,3);
      pdb->current->atom.resNumber=atoi(&str[25]);
      pdb->current->atom.tempFactor=atof(&str[62]);
      pdb->current->atom.occupancy=atof(&str[56]);
      strncpy(pdb->current->atom.atomName,str+13,3);
      strncpy(pdb->current->atom.element,str+77,1);
      
      pdb->current->nextAtom->nextAtom=NULL;
      pdb->current=pdb->current->nextAtom;
      
      if(strstr(str," CA ")!=NULL){
        pdb->numCA++;
        
        pdb->currentCA->nextCA=(recordPDB*)malloc(sizeof(recordPDB));
        
        pdb->currentCA->atom.x=atof(&str[30]);
        pdb->currentCA->atom.y=atof(&str[38]);
        pdb->currentCA->atom.z=atof(&str[46]);
        strncpy(pdb->currentCA->atom.resName,str+17,3);
        pdb->currentCA->atom.resNumber=atoi(&str[25]);
        pdb->currentCA->atom.tempFactor=atof(&str[62]);
        pdb->currentCA->atom.occupancy=atof(&str[56]);
        strncpy(pdb->currentCA->atom.atomName,str+13,3);
        strncpy(pdb->currentCA->atom.element,str+77,1);
        
        pdb->currentCA->nextCA->nextCA=NULL;
        pdb->currentCA=pdb->currentCA->nextCA;
      }
    }
  }

  
  
  return pdb->numAtom;
}
