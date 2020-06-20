#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl.h"
#include "bst.h"
#include "rb.h"

int avl_height, bst_height, rb_height;
int min_avl[3]={100,100,100}, max_avl[3]={0, 0, 0};
int min_bst[3]={100,100,100}, max_bst[3]={0, 0, 0};
int min_rb[3]={100,100,100}, max_rb[3]={0, 0, 0};
double avg_avl[3]={0,0,0}, avg_bst[3]={0,0,0}, avg_rb[3]={0, 0, 0};

void postorder_integer_avl(const struct avl_node *node, int height){
  if(height>avl_height)
    avl_height=height;
  if (node == NULL)
    return ;

  if (node->avl_link[0] != NULL || node->avl_link[1] != NULL){
      postorder_integer_avl(node->avl_link[0], height+1);
      postorder_integer_avl(node->avl_link[1], height+1);
  }
}

void postorder_integer_bst(const struct bst_node *node, int height){
  if(height>bst_height)
    bst_height=height;
  if (node == NULL)
    return;

  if (node->bst_link[0] != NULL || node->bst_link[1] != NULL){
      postorder_integer_bst(node->bst_link[0], height+1);
      postorder_integer_bst(node->bst_link[1], height+1);
  }
}

void postorder_integer_rb(const struct rb_node *node, int height){
  if(height>rb_height)
    rb_height=height;
  if (node == NULL)
    return;

  if (node->rb_link[0] != NULL || node->rb_link[1] != NULL){
      postorder_integer_rb(node->rb_link[0],height+1);
      postorder_integer_rb(node->rb_link[1],height+1);
  }
}

int int_compare(const void *pa, const void *pb, void *param)
{
  int a = *(const int *)pa;
  int b = *(const int *)pb;

  if (a < b)
    return -1;
  else if (a > b)
    return +1;
  else
    return 0;
}


int main(){
  int num_iter=10000;
  srand(time(NULL));

  for(int times=0;times<num_iter;times++){
  int random1[2048];
  for(int j=0;j<2048;j++)
    random1[j]=j;
  for(int j=2047;j>=0;j--){
    int r=rand()%2048;
    if(r%2==0)
      random1[r]=-random1[r];
    int tmp=random1[j];
    random1[j]=random1[r];
    random1[r]=tmp;
  }

  struct avl_table *avltree;  
  avltree = avl_create(int_compare, NULL, NULL);
  struct bst_table *bsttree;
  bsttree = bst_create(int_compare, NULL, NULL);
  struct rb_table *rbtree;
  rbtree = rb_create(int_compare, NULL, NULL);

  int i;
  for(i=0;i<2048;i++){
    int* element = (int*)malloc(sizeof(int));
    *element = random1[i];
    void **p1 = avl_probe(avltree, element);
    void **p2 = bst_probe(bsttree, element);
    void **p3 = rb_probe(rbtree, element);
  }
  
  postorder_integer_avl(avltree->avl_root, 0);
  postorder_integer_bst(bsttree->bst_root, 0);
  postorder_integer_rb(rbtree->rb_root, 0);

  if(avl_height < min_avl[0])
    min_avl[0]=avl_height;
  if(avl_height > max_avl[0])
    max_avl[0]=avl_height;
  avg_avl[0]+=(double)avl_height/num_iter;

  if(bst_height < min_bst[0])
    min_bst[0]=bst_height;
  if(bst_height > max_bst[0])
    max_bst[0]=bst_height;
  avg_bst[0]+=(double)bst_height/num_iter;

  if(rb_height < min_rb[0])
    min_rb[0]=rb_height;
  if(rb_height > max_rb[0])
    max_rb[0]=rb_height;
  avg_rb[0]+=(double)rb_height/num_iter;

  for(i=0;i<1024;i++){
    int *element = (int*)malloc(sizeof(int));
    *element=random1[i];
    void *p1=avl_delete(avltree, element);
    void *p2=bst_delete(bsttree, element);
    void *p3=rb_delete(rbtree, element);
  }

  avl_height=0;
  bst_height=0;
  rb_height=0;

  postorder_integer_avl(avltree->avl_root, 0);
  postorder_integer_bst(bsttree->bst_root, 0);
  postorder_integer_rb(rbtree->rb_root, 0);

  if(avl_height < min_avl[1])
    min_avl[1]=avl_height;
  if(avl_height > max_avl[1])
    max_avl[1]=avl_height;
  avg_avl[1]+=(double)avl_height/num_iter;

  if(bst_height < min_bst[1])
    min_bst[1]=bst_height;
  if(bst_height > max_bst[1])
    max_bst[1]=bst_height;
  avg_bst[1]+=(double)bst_height/num_iter;

  if(rb_height < min_rb[1])
    min_rb[1]=rb_height;
  if(rb_height > max_rb[1])
    max_rb[1]=rb_height;
  avg_rb[1]+=(double)rb_height/num_iter;

  int random2[2048];
  for(int j=0;j<2048;j++)
    random2[j]=j+2048;
  for(int j=2047;j>=0;j--){
    int r=rand()%2048;
    if(r%2==0)
      random2[r]=-random2[r];
    int tmp=random2[j];
    random2[j]=random2[r];
    random2[r]=tmp;
  }

  for(i=0;i<2048;i++){
    int* element = (int*)malloc(sizeof(int));
    *element = random2[i];
    void **p1 = avl_probe(avltree, element);
    void **p2 = bst_probe(bsttree, element);
    void **p3 = rb_probe(rbtree, element);
  }


  avl_height=0;
  bst_height=0;
  rb_height=0;

  postorder_integer_avl(avltree->avl_root, 0);
  postorder_integer_bst(bsttree->bst_root, 0);
  postorder_integer_rb(rbtree->rb_root, 0);

  if(avl_height < min_avl[2])
    min_avl[2]=avl_height;
  if(avl_height > max_avl[2])
    max_avl[2]=avl_height;
  avg_avl[2]+=(double)avl_height/num_iter;

  if(bst_height < min_bst[2])
    min_bst[2]=bst_height;
  if(bst_height > max_bst[2])
    max_bst[2]=bst_height;
  avg_bst[2]+=(double)bst_height/num_iter;

  if(rb_height < min_rb[2])
    min_rb[2]=rb_height;
  if(rb_height > max_rb[2])
    max_rb[2]=rb_height;
  avg_rb[2]+=(double)rb_height/num_iter;
}

  //printf("%f %f %f\n",avl_height/num_iter, bst_height/num_iter, rb_height/num_iter);
  //printf("%f %f %f\n", avg_avl[2], avg_bst[2], avg_rb[2]);

  printf("after first insertion\n");
  printf("bst %d %d %d\n", max_bst[0], min_bst[0], (int)avg_bst[0]);
  printf("avl %d %d %d\n", max_avl[0], min_avl[0], (int)avg_avl[0]);
  printf("rb %d %d %d\n", max_rb[0], min_rb[0], (int)avg_rb[0]);
  printf("after removal\n");
  printf("bst %d %d %d\n", max_bst[1], min_bst[1], (int)avg_bst[1]);
  printf("avl %d %d %d\n", max_avl[1], min_avl[1], (int)avg_avl[1]);
  printf("rb %d %d %d\n", max_rb[1], min_rb[1], (int)avg_rb[1]);
  printf("after 2nd insertion\n");
  printf("bst %d %d %d\n", max_bst[2], min_bst[2], (int)avg_bst[2]);
  printf("avl %d %d %d\n", max_avl[2], min_avl[2], (int)avg_avl[2]);
  printf("rb %d %d %d\n", max_rb[2], min_rb[2], (int)avg_rb[2]);

  return 0;
}
