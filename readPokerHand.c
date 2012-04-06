/*
 * readPokerHand.c
 *
 * Sáskya Gurgel, 2012-04-06
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mlpnnets.h"

#define TRUE    1
#define FALSE   0

#define SEED                  631814

#define EPOCHS                7000
#define LEARNING_RATE         0.003

#define MAX(a, b)             (a >= b? a : b)

typedef enum tagClass {
    Nothing_in_hand, 
    One_Pair, 
    Two_pairs, 
    Three_of_a_kind, 
    Straight, 
    Flush, 
    Full_house, 
    Four_of_a_kind, 
    Straight_flush, 
    Royal_flush
} Class;

DataSet* read_dataset(char *filename)
{
    FILE    *f;
    int     done = FALSE, i, j;

    double S1, C1, S2, C2, S3, C3, S4, C4, S5, C5, CLASS;
                                             
    DataSet *dset;
    
    char buffer[140];
        
    dset = (DataSet*) malloc(sizeof(DataSet));
    if (dset == NULL) {
        fprintf(stderr, "Could not allocate memory\n");
        return NULL;
    }
          
    f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "File not found: %s\n", filename);
        free(dset);
        return NULL;
    }
       
    // count lines in file to allocate dataset arrays
    i = 0;
    while (fgets(buffer, 140, f) != NULL)
        ++i;

    if (!feof(f) || ferror(f)) {
        fprintf(stderr, "IO error while reading from file\n");
        free(dset);
        fclose(f);
        return NULL;
    }
    fseek(f, 0, SEEK_SET);
                
    // prepare dataset
    dset->n_cases = i;
    dset->input_size = 10;
    dset->output_size = 10;
    allocate_dataset_arrays(dset);
               
    i = 0;
    while (!done) {
        j = fscanf(f, "%lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf \n", 
                      &S1, &C1, &S2, &C2, &S3, &C3, &S4, &C4, &S5, &C5, &CLASS);

/*        printf("%lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf \n", 
                      S1, C1, S2, C2, S3, C3, S4, C4, S5, C5, CLASS);*/
        if (j != 11)
            done = TRUE;
        else {

            dset->input[i][0] = S1;
            dset->input[i][1] = C1;
            dset->input[i][2] = S2;
            dset->input[i][3] = C2;
            dset->input[i][4] = S3;            
            dset->input[i][5] = C3;            
            dset->input[i][6] = S4;            
            dset->input[i][7] = C4;            
            dset->input[i][8] = S5;            
            dset->input[i][9] = C5;            
           
            if (CLASS==0) {
                dset->output[i][0] = 0.9;
                dset->output[i][1] = 0.1;
                dset->output[i][2] = 0.1;
                dset->output[i][3] = 0.1;
                dset->output[i][4] = 0.1;
                dset->output[i][5] = 0.1;
                dset->output[i][6] = 0.1;
                dset->output[i][7] = 0.1;
                dset->output[i][8] = 0.1;
                dset->output[i][9] = 0.1;
               
            } else if (CLASS==1) {
                dset->output[i][0] = 0.1;
                dset->output[i][1] = 0.9;
                dset->output[i][2] = 0.1;
                dset->output[i][3] = 0.1;
                dset->output[i][4] = 0.1;
                dset->output[i][5] = 0.1;
                dset->output[i][6] = 0.1;
                dset->output[i][7] = 0.1;
                dset->output[i][8] = 0.1;
                dset->output[i][9] = 0.1;
                
            } else if (CLASS==2) {
                dset->output[i][0] = 0.1;
                dset->output[i][1] = 0.1;
                dset->output[i][2] = 0.9;
                dset->output[i][3] = 0.1;
                dset->output[i][4] = 0.1;
                dset->output[i][5] = 0.1;
                dset->output[i][6] = 0.1;
                dset->output[i][7] = 0.1;
                dset->output[i][8] = 0.1;
                dset->output[i][9] = 0.1;
               
            } else if (CLASS==3) {
                dset->output[i][0] = 0.1;
                dset->output[i][1] = 0.1;
                dset->output[i][2] = 0.1;
                dset->output[i][3] = 0.9;
                dset->output[i][4] = 0.1;
                dset->output[i][5] = 0.1;
                dset->output[i][6] = 0.1;
                dset->output[i][7] = 0.1;
                dset->output[i][8] = 0.1;
                dset->output[i][9] = 0.1;
               
            } else if (CLASS==4) {
                dset->output[i][0] = 0.1;
                dset->output[i][1] = 0.1;
                dset->output[i][2] = 0.1;
                dset->output[i][3] = 0.1;
                dset->output[i][4] = 0.9;
                dset->output[i][5] = 0.1;
                dset->output[i][6] = 0.1;
                dset->output[i][7] = 0.1;
                dset->output[i][8] = 0.1;
                dset->output[i][9] = 0.1;
               
            } else if (CLASS==5) {
                dset->output[i][0] = 0.1;
                dset->output[i][1] = 0.1;
                dset->output[i][2] = 0.1;
                dset->output[i][3] = 0.1;
                dset->output[i][4] = 0.1;
                dset->output[i][5] = 0.9;
                dset->output[i][6] = 0.1;
                dset->output[i][7] = 0.1;
                dset->output[i][8] = 0.1;
                dset->output[i][9] = 0.1;
               
            } else if (CLASS==6) {
                dset->output[i][0] = 0.1;
                dset->output[i][1] = 0.1;
                dset->output[i][2] = 0.1;
                dset->output[i][3] = 0.1;
                dset->output[i][4] = 0.1;
                dset->output[i][5] = 0.1;
                dset->output[i][6] = 0.9;
                dset->output[i][7] = 0.1;
                dset->output[i][8] = 0.1;
                dset->output[i][9] = 0.1;
               
            } else if (CLASS==7) {
                dset->output[i][0] = 0.1;
                dset->output[i][1] = 0.1;
                dset->output[i][2] = 0.1;
                dset->output[i][3] = 0.1;
                dset->output[i][4] = 0.1;
                dset->output[i][5] = 0.1;
                dset->output[i][6] = 0.1;
                dset->output[i][7] = 0.9;
                dset->output[i][8] = 0.1;
                dset->output[i][9] = 0.1;
               
            } else if (CLASS==8) {
                dset->output[i][0] = 0.1;
                dset->output[i][1] = 0.1;
                dset->output[i][2] = 0.1;
                dset->output[i][3] = 0.1;
                dset->output[i][4] = 0.1;
                dset->output[i][5] = 0.1;
                dset->output[i][6] = 0.1;
                dset->output[i][7] = 0.1;
                dset->output[i][8] = 0.9;
                dset->output[i][9] = 0.1;
               
            } else { 
                dset->output[i][0] = 0.1;
                dset->output[i][1] = 0.1;
                dset->output[i][2] = 0.1;
                dset->output[i][3] = 0.1;
                dset->output[i][4] = 0.1;
                dset->output[i][5] = 0.1;
                dset->output[i][6] = 0.1;
                dset->output[i][7] = 0.1;
                dset->output[i][8] = 0.1;
                dset->output[i][9] = 0.9;
                               
            }
            
            ++i;
        }

    }

    fclose(f);                                                                                                       
    return dset;
}

void print_dataset(DataSet *dset)
{
    int i, j;

    printf("Number of cases: %d\n", dset->n_cases);
    for (i = 0; i < dset->n_cases; ++i) {
        for (j = 0; j < dset->input_size; ++j)
            printf("%3.2f ", dset->input[i][j]);
        printf(" | ");
        for (j = 0; j < dset->output_size; ++j)
            printf("%3.2f ", dset->output[i][j]);
        printf("\n");
    }
}

Class output_to_class(double *output)
{
    double max;
    
    max = MAX(output[0], MAX(output[1], MAX(output[2], MAX(output[3], MAX(output[4], MAX(output[5], MAX(output[6], MAX(output[7], MAX(output[8], output[9])))))))));
    if (output[0] == max)
        return Nothing_in_hand;
    else if (output[1] == max)
        return One_Pair;
    else if (output[2] == max)
        return Two_pairs;
    else if (output[3] == max)
        return Three_of_a_kind;
    else if (output[4] == max)
        return Straight;
    else if (output[5] == max)
        return Flush;
    else if (output[6] == max)
        return Full_house;
    else if (output[7] == max)
        return Four_of_a_kind;
    else if (output[8] == max)
        return Straight_flush;
    return Royal_flush;
}

Class predict_class(Network *nnet, double *input)
{
    forward_prop(nnet, sigmoid, input);
    return output_to_class(nnet->output_layer->y);
}

char    *n0 = "0 - Nothing in hand";
char    *n1 = "1 - One Pair ";
char    *n2 = "2 - Two pairs";
char    *n3 = "3 - Three of a kind";
char    *n4 = "4 - Straight";
char    *n5 = "5 - Flush";
char    *n6 = "6 - Full house";
char    *n7 = "7 - Four of a kind";
char    *n8 = "8 - Straight flush";
char    *n9 = "9 - Royal flush";
    
char *class_to_string(Class c)
{
    char *res;
    
    switch(c) {
    case Nothing_in_hand:
        res = n0;
        break;
    case One_Pair:
        res = n1;
        break;
    case Two_pairs:
        res = n2;
        break;    
    case Three_of_a_kind:
        res = n3;
        break;
    case Straight:
        res = n4;
        break;
    case Flush:
        res = n5;
        break;
    case Full_house:
        res = n6;
        break;    
    case Four_of_a_kind:
        res = n7;
        break;    
    case Straight_flush:
        res = n8;
        break;    
    default:
        res = n9;
    }
    return res;
}

int main(int argc, char **argv)
{
    int     i;
    int     errors;
    DataSet *train_set;
    DataSet *test_set;
    Network *poker_hand = create_network(14);
    double  e;
    double  acc;
    Class   predicted, desired;

    // training
    train_set = read_dataset("poker-hand.train");

    if (train_set == NULL) {
        fprintf(stderr, "Error reading training set\n");
        exit(1);
    }

    add_layer(poker_hand, 25);  // hidden layer
    add_layer(poker_hand, 10);  // output layer
    initialize_weights(poker_hand, SEED);
    print_network_structure(poker_hand);

    printf("Training network with %d epochs...\n", EPOCHS);
    e = batch_train(poker_hand, train_set, LEARNING_RATE, EPOCHS,
                    sigmoid, dsigmoid);
    printf("Training finished, approximate final SSE: %f\n", e);

    print_network_structure(poker_hand);

    // testing
    test_set = read_dataset("poker-hand.test");

    if (test_set == NULL) {
        fprintf(stderr, "Error reading test set\n");
        exit(1);
    }

    errors = 0;
    printf("Testing with %d cases...\n", test_set->n_cases);
    for (i = 0; i < test_set->n_cases; ++i) {
        predicted = predict_class(poker_hand, test_set->input[i]);
        desired = output_to_class(test_set->output[i]);
        if (predicted != desired)
            ++errors;
        /*printf("Case %d | predicted: %s, desired: %s, outputs: %4.3f %4.3f \n", i,
               class_to_string(predicted), class_to_string(desired),
               poker_hand->output_layer->y[0], poker_hand->output_layer->y[1]);*/
    }

    acc = 100.0 - (100.0 * errors / test_set->n_cases);
    printf("Testing accuracy: %f\n", acc);
    printf("Total classificarion errors: %d\n", errors);
    system("pause");
    return 0;
}
