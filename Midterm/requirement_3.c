#include <stdio.h>
#define MAX_N 20

int set[MAX_N];
int n;

int findRoot(int x){
    if(set[x] == x){
        return x;
    }
    set[x] = findRoot(set[x]);
    return set[x];
}

void uni(int x, int y){
    int xRoot = findRoot(x);
    int yRoot = findRoot(y);
    set[xRoot] = yRoot;
}

int CountSet(){
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if(set[i] == i){count += 1;}
    }
    return count;
}

int main() {
    // Input

    int cycle_x = -1, cycle_y = -1;     // The edge (x, y) used to determine whether there is a cycle, x < y
    int has_cycle = 0;      // Used to determine whether there is a cycle
    
    // Read the number of nodes
    int not = scanf("%d", &n);

    int graph[n][n];
    
    // Read adjacency matrix
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int not2 = scanf("%d", &graph[i][j]);
        }
    }

    for (int i = 0; i < n; i++)
    {
        set[i] = i;
    }
    int rec_x,rec_y;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(graph[i][j] == 0){
                continue;
            }
            if(i>j){
                // rec_x = i;
                // rec_y = j;
                continue;
            }
            if(findRoot(i) != findRoot(j)){
                uni(i,j);
                rec_x = i;
                rec_y = j;
                continue;
            }else{
                has_cycle = 1;
                cycle_x = i;
                cycle_y = j;
                break;
            }
        }
        if(has_cycle == 1){
            break;
        }
    }
    if(has_cycle == 0){
        if(rec_x > rec_y){
            cycle_x = rec_y;
            cycle_y = rec_x;
        }else{
            cycle_x = rec_x;
            cycle_y = rec_y;
        }
        // cycle_x = rec_x;
        // cycle_y = rec_y;
    }

    // Output
    if(has_cycle) {
        printf("True,(%d,%d)\n", cycle_x, cycle_y);
    } else {
        printf("False,(%d,%d)\n", cycle_x, cycle_y);
    }
    
    
    return 0;
}