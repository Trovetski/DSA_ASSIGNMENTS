# include<stdio.h>
# include<stdlib.h>
# define bool int

typedef struct NODE{
    int data;
    struct NODE* left;
    struct NODE* right;
    int height;

}node;

node * root = NULL;

node * newNode(int data){
    node * nd = (node*) malloc(sizeof(node));
    nd->data = data;
    nd->left = NULL;
    nd->right = NULL;
    nd->height = 1;
    return nd;

}

int checkHeight(node * nd){
    if(nd == NULL) return 0;

    else
    {
        return nd->height;
    }        
}

int max(int a , int b){
    if (a>b){
        return a;
    }

    else{
        return b;
    }
        
}


int balanceFactor(node * nd){
    if (nd == NULL) return 0;

    else
    {
        return checkHeight(nd->right) - checkHeight(nd->left);
    }
}

int undateHeight(node*nd){
    if(nd == NULL) return 0;

    else{
        nd->height = 1 + max(checkHeight(nd->left),checkHeight(nd->right));
        return nd->height; 
    }
}

node * leftRot(node*nd){
    node * a = nd->right;
    node * newnd = a->left;

    a->left = nd;
    nd->right = newnd;

    undateHeight(nd);
    undateHeight(a);

    return a;
}

node * rightRot(node*nd){
    node * a = nd->left;
    node * newnd = a->right;

    a->right = nd;
    nd->left = newnd;

    undateHeight(nd);
    undateHeight(a);

    return a;
}

node * insertINtree(node*nd ,int data){

    if(nd == NULL){
        
        nd = newNode(data);
    }

    else if(data < nd->data){
        nd->left = insertINtree(nd->left,data);
    }

    else if(data > nd->data){
        nd->right = insertINtree(nd->right,data);
    }

    undateHeight(nd);

    int balanceFac = balanceFactor(nd);

    if(balanceFac <-1){
        // left left
        if(nd->left->data > data){
            nd = rightRot(nd);
        }

        // left right
        else if(nd->left->data < data){
            nd->left = leftRot(nd->left);
            nd = rightRot(nd);
        }   
    }

    else if(balanceFac > 1){
        // right right
        if(nd->right->data < data){
            nd = leftRot(nd);
        }

        // right left
        else if(nd->right->data > data){
            nd->right = rightRot(nd->right);
            nd = leftRot(nd);
        }
    }

    return nd;

}

void InOrder(node *nd)
{
    
    if (nd != NULL)
    {
        int balanceFac = balanceFactor(nd);
        InOrder(nd->left);
        printf("(%d ,%d, %d)\n", nd->data,undateHeight(nd),balanceFac);
        InOrder(nd->right);
    }
}

void preOrder(node *ptr)
{
    if (ptr != NULL)
    {
        printf("%d ", ptr->data);
        preOrder(ptr->left);
        preOrder(ptr->right);
    }
}

node * deleteNode(node*nd, int data){
    if(nd==NULL){
        return NULL;
    }

    else if(data < nd->data){
        nd->left = deleteNode(nd->left,data);
    }

    else if(data > nd->data){
        nd->right = deleteNode(nd->right,data);
    }

    else
    {
        if((nd->left == NULL) && (nd->right == NULL)){
            
            free(nd);
            return NULL;
        }

        else if(nd->left == NULL){
            
            node * temp = nd->right;
            free(nd);
            nd = temp;
        }

        else if(nd->right == NULL){
            
            node * temp = nd->left;
            free(nd);
            nd = temp;
        }

        else
        {   
            
            node * temp = nd->left;
            while(temp->right != NULL){
                temp = temp->right;
            }
        
            nd->data = temp->data;
            nd->left = deleteNode(nd->left,temp->data);
        }
    }

    undateHeight(nd);
    int balanceFac = balanceFactor(nd);
    
    if(balanceFac <-1){
        // left left
        if(balanceFactor(nd->left) < 0){
            nd = rightRot(nd);
        }

        // left right
        else if(balanceFactor(nd->left) >= 0){
            nd->left = leftRot(nd->left);
            nd = rightRot(nd);
        }   
    }

    else if(balanceFac > 1){
        // right right
        if(balanceFactor(nd->right) > 0){
            nd = leftRot(nd);
        }

        // right left
        else if(balanceFactor(nd->right) <= 0){
            nd->right = rightRot(nd->right);
            nd = leftRot(nd);
        }
    }

    return nd;
}

bool search(node *ptr, int data){
    if(ptr == NULL){
        return -1;
    }

    else if(ptr->data == data){
        return 0;
    }

    else if(data < ptr->data){
        return search(ptr->left, data);
    }

    else if(data > ptr->data){
        return search(ptr->right, data);
    }
}

int main(){

    int i = 0;
    int choice = 0;
    int option = 0;
    int data = 0;

    do
    {
        printf("Give your choice :");
        scanf("%d",&choice);

        if(choice > 4 || choice == 0){
            printf("\n!!!Quitting the program!!!\n");
            break;
        }

        else{
            switch (choice)
            {
            case 1:
                // create tree
                
                printf("Please give your input : \n");
                do
                {
                    scanf("%d",&i);
                    root = insertINtree(root,i);
                } while (getchar() != '\n');

            break;
        
            case 2 :
                // insert node
                
                printf("Give the value that you want to insert :");
                scanf("%d",&data);
                root = insertINtree(root,data);

            break;

            case 3 :
                // deleting a node
                
                printf("Give the node that you want to delete :");
                scanf("%d",&data);

                if(search(root,data) == 0){
                    //printf("FOUND\n");
                    root = deleteNode(root,data);
                }

                else if(search(root,data) == -1){
                    printf("NOT FOUND\n");
                }

            break;

            case 4 :
                // inorder traversal
                printf("This is the in order traversal of the tree=> \n");
                InOrder(root);
                //preOrder(root);

            break;

            default:
                printf("Please input a valid input !!!");
            break;
            }
        }

        printf("\nIf you want to continue input 1 :");
        scanf("%d",&option);
    } while (option == 1);
    

    return 0;
}   