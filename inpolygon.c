#include <stdio.h>
#include <stdlib.h>

#define INSIDE 0
#define ONSIDE 1
#define OUTSIDE 2

#define TOL 0.0001
#define ABS(a) ((a)>=0?(a):-(a))

typedef struct{
    double x;
    double y;
}point;

typedef struct{
    int numpoint;
    point *pointlist; 
}polygon;

void polygoninit(polygon **pol, int num, double *points){
	(*pol) = (polygon*)malloc(sizeof(int)+sizeof(point*));
        (*pol)->pointlist = (point*)malloc(sizeof(point)*num);
        (*pol)->numpoint = num;
        for(int i=0; i<num; i++){
            point *p = (*pol)->pointlist+i;
            p->x = points[2*i];
            p->y = points[2*i+1];
        }
}
void polygonfree(polygon **pol){
    free((*pol)->pointlist);
    free(*pol);
    *pol = NULL;
}
double calpolygonarea(polygon *pol){
    double area = 0; 
    for(int i=0; i<pol->numpoint; ++i){
        point *p1 = pol->pointlist+i;
        point *p2 = i==pol->numpoint-1?pol->pointlist:pol->pointlist+i+1;
       area += (p1->y+p2->y)*(p1->x-p2->x);
    }
    return area*0.5;
}
double cross(point* ref, point *p1, point *p2){
    double x1 = ref->x-p1->x;
    double y1 = ref->y-p1->y;
    double x2 = p2->x-p1->x;
    double y2 = p2->y-p1->y;
    return x1*y2-y1*x2;
}

int raycasting(polygon *pol, point *ref){
    int count = 0;
    for(int i=0; i<pol->numpoint; ++i){
        point *p1 = pol->pointlist+i;
        point *p2 = i==pol->numpoint-1?pol->pointlist:pol->pointlist+i+1;
        if((ref->y>=p1->y&&ref->y<=p2->y) || (ref->y>=p2->y&&ref->y<=p1->y)){
            double t = (ref->y-p1->y)/(p2->y-p1->y);
            double xt = p1->x+t*(p2->x-p1->x);
            if(ref->x==xt) return ONSIDE;
            if(ref->x<xt) ++count;
        }
    }
    return count%2?INSIDE:OUTSIDE;
}
int areacheck(polygon *pol, point *ref){
    double polygonarea = calpolygonarea(pol);
    double triarea = 0;
    for(int i=0; i<pol->numpoint; i++){
        point *p1 = pol->pointlist+i;
        point *p2 = i==pol->numpoint-1?pol->pointlist:pol->pointlist+i+1;
        double area = ABS(cross(ref, p1, p2));
        if(area==0) return ONSIDE;
        triarea += 0.5*area;
    }
    return ABS(polygonarea-triarea)<TOL?INSIDE:OUTSIDE;
}
int crosscheck(polygon *pol, point *ref){
    for(int i=0; i<pol->numpoint; i++){
        point *p1 = pol->pointlist+i;
        point *p2 = i==pol->numpoint-1?pol->pointlist:pol->pointlist+i+1;
        double cr = cross(ref, p1, p2);
        if(cr>0) return OUTSIDE;
	if(cr==0) return ONSIDE;
    }
    return INSIDE;
}

int arclengthcheck(polygon *pol, point *ref){
    int arc = 0, q1, q2; 
    double x1, y1, x2, y2;
    for(int i=0; i<pol->numpoint; i++){
        point *p1 = pol->pointlist+i;
        point *p2 = i==pol->numpoint-1?pol->pointlist:pol->pointlist+i+1;
        double cr = cross(p1, ref, p2);
        if(cr==0) return ONSIDE; 
	x1 = p1->x-ref->x;
	y1 = p1->y-ref->y;
        x2 = p2->x-ref->x;
        y2 = p2->y-ref->y;
        q1 = x1>0?(y1>0?0:3):(y1>0?1:2);
        q2 = x2>0?(y2>0?0:3):(y2>0?1:2);
        int g = (q2-q1+4)%4;
        if(g==1) arc++;
        else if(g==3) arc--;
        else if(g==2) cr>0?(arc+=2):(arc-=2);  
    }
    return arc==0?OUTSIDE:INSIDE;
}

int main(int argc, char **argv){
    double points[10] = {0,0,10,0,10,20,5,25,0,20};
    polygon *pol = NULL;
    polygoninit(&pol, 5, points);
    point in, on, out;
    in.x = 5;  in.y = 10;
    on.x = 10;  on.y = 10;
    out.x = 7;  out.y = 24;
    printf("in state by ray: %d \n", raycasting(pol, &in));
    printf("on state by ray: %d \n", raycasting(pol, &on));
    printf("out state by ray: %d \n", raycasting(pol, &out));
/*===============*/
    printf("in state by areacheck: %d \n", areacheck(pol, &in));
    printf("on state by areacheck: %d \n",areacheck(pol, &on));
    printf("out state by areacheck: %d \n",areacheck(pol, &out));
/*===============*/
    printf("in state by crosscheck: %d \n", crosscheck(pol, &in));
    printf("on state by crosscheck: %d \n",crosscheck(pol, &on));
    printf("out state by crosscheck: %d \n",crosscheck(pol, &out));
/*===============*/
    printf("in state by arccheck: %d \n", arclengthcheck(pol, &in));
    printf("on state by arccheck: %d \n", arclengthcheck(pol, &on));
    printf("out state by arccheck: %d \n",arclengthcheck(pol, &out));
    polygonfree(&pol);
    return 0;
}
