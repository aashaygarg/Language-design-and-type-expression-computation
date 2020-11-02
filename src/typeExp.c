#include "typeExp.h"
#include "Tree.h"
#include "sourceTokenizer.h"
#include <stdio.h>
#include<stdlib.h>

typex_table create_Typex_Table(){
    typex_table txp_table;
    txp_table.head = NULL;
    txp_table.tail = NULL;
    return txp_table;
}

LINK createLink(typex_table table, typeCell tpc){
    LINK l;
    l.t = tpc;
    table.tail->next = &l;
    table.tail = table.tail->next;
}

/*********************************************
typex_table typeexpression(tokenStream src){
    NODE* rn = src.head;
    //I am considering name of ds to be typeex.
    typex_table op = create_Typex_Table();
    while(rn){
        if(rn->ele.name = DECLARE){
            rn = rn->next;
            int i = 0;
            if(rn->ele.name = LIST){
                rn = rn->next->next->next;
                while(rn->ele.name = ID){
                    i++;
                    
                    //add var to table
                    rn = rn->next;
                }
            }
            else{
                i++;
                //add var to table
            }
            rn = rn->next;
            token_name tn = rn->ele.name;
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
******************************************************/
typex_table typeexpression(tree_node root){
    
}
