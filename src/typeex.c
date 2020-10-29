#include<stdio.h>
#include"sourceTokenizer.c"

typeex typeexpression(tokenStream src){
    NODE rn = src->head;
    //I am considering name of ds to be typeex.
    typeex op;
    while(rn){
        if(rn->ele->name = DECLARE){
            rn = rn->next;
            int i = 0;
            if(rn->ele->name = list){
                rn = rn->next->next->next;
                while(rn->ele->name = VARIABLES){
                    i++;
                    //add var to table
                }
            }
            else{
                i++;
                //add var to table
            }
            rn = rn->next->next;
            token_name tn = rn->ele->name;
            for(int j=0; j<i; j++){
                //add token name to table for all i var
            }
            if (tn = ARRAY){
                //check no of dimensions
            }
            else if (tn = JAGGED){
                //check subsequent lines
            }
            else{
                //just add NA wherever needed
            }
        }
        rn = rn->next;
    }
    return op;
}