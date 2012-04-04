/*
 * readAdult.c
 *
 * Sáskya Gurgel, 2012-04-02
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
    Spruce_Fir,
    Lodgepole_Pine,
    Ponderosa_Pine,
    Cottonwood_Willow,
    Aspen,
    Douglas_fir,
    Krummholz
} Class;

DataSet* read_dataset(char *filename)
{
    FILE    *f;
    int     done = FALSE, i, j, k;

    double Elevation_quantitative, Aspect_quantitative, Slope_quantitative, Horizontal_Distance_To_Hydrology_quantitative,
           Vertical_Distance_To_Hydrology_quantitative, Horizontal_Distance_To_Roadways_quantitative, Hillshade_9am_quantitative, 
           Hillshade_Noon_quantitative, Hillshade_3pm_quantitative, Horizontal_Distance_To_Fire_Points_quantitative, 
           Wilderness_Area_1, Wilderness_Area_2, Wilderness_Area_3, Wilderness_Area_4, 
           Soil_Type1, Soil_Type2, Soil_Type3, Soil_Type4, Soil_Type5, Soil_Type6, Soil_Type7, Soil_Type8, Soil_Type9, Soil_Type10, 
           Soil_Type11, Soil_Type12, Soil_Type13, Soil_Type14, Soil_Type15, Soil_Type16, Soil_Type17, Soil_Type18, Soil_Type19, Soil_Type20, 
           Soil_Type21, Soil_Type22, Soil_Type23, Soil_Type24, Soil_Type25, Soil_Type26, Soil_Type27, Soil_Type28, Soil_Type29, Soil_Type30, 
           Soil_Type31, Soil_Type32, Soil_Type33, Soil_Type34, Soil_Type35, Soil_Type36, Soil_Type37, Soil_Type38, Soil_Type39, Soil_Type40, 
           Cover_Type;
                                             
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
    dset->input_size = 54;
    dset->output_size = 7;
    allocate_dataset_arrays(dset);
            
    i = 0;
    while (!done) {
        j = fscanf(f, "%lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf \n", 
                      &Elevation_quantitative, &Aspect_quantitative, &Slope_quantitative, &Horizontal_Distance_To_Hydrology_quantitative, 
                      &Vertical_Distance_To_Hydrology_quantitative, &Horizontal_Distance_To_Roadways_quantitative, &Hillshade_9am_quantitative, 
                      &Hillshade_Noon_quantitative, &Hillshade_3pm_quantitative, &Horizontal_Distance_To_Fire_Points_quantitative, 
                      &Wilderness_Area_1, &Wilderness_Area_2, &Wilderness_Area_3, &Wilderness_Area_4, 
                      &Soil_Type1, &Soil_Type2, &Soil_Type3, &Soil_Type4, &Soil_Type5, &Soil_Type6, &Soil_Type7, &Soil_Type8, &Soil_Type9, &Soil_Type10, 
                      &Soil_Type11, &Soil_Type12, &Soil_Type13, &Soil_Type14, &Soil_Type15, &Soil_Type16, &Soil_Type17, &Soil_Type18, &Soil_Type19, &Soil_Type20, 
                      &Soil_Type21, &Soil_Type22, &Soil_Type23, &Soil_Type24, &Soil_Type25, &Soil_Type26, &Soil_Type27, &Soil_Type28, &Soil_Type29, &Soil_Type30, 
                      &Soil_Type31, &Soil_Type32, &Soil_Type33, &Soil_Type34, &Soil_Type35, &Soil_Type36, &Soil_Type37, &Soil_Type38, &Soil_Type39, &Soil_Type40, 
                      &Cover_Type);

        /*printf("%lf, %f, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf\n", 
                      Elevation_quantitative, Aspect_quantitative, Slope_quantitative, Horizontal_Distance_To_Hydrology_quantitative, 
                      Vertical_Distance_To_Hydrology_quantitative, Horizontal_Distance_To_Roadways_quantitative, Hillshade_9am_quantitative, 
                      Hillshade_Noon_quantitative, Hillshade_3pm_quantitative, Horizontal_Distance_To_Fire_Points_quantitative, 
                      Wilderness_Area_1, Wilderness_Area_2, Wilderness_Area_3, Wilderness_Area_4, 
                      Soil_Type1, Soil_Type2, Soil_Type3, Soil_Type4, Soil_Type5, Soil_Type6, Soil_Type7, Soil_Type8, Soil_Type9, Soil_Type10, 
                      Soil_Type11, Soil_Type12, Soil_Type13, Soil_Type14, Soil_Type15, Soil_Type16, Soil_Type17, Soil_Type18, Soil_Type19, Soil_Type20, 
                      Soil_Type21, Soil_Type22, Soil_Type23, Soil_Type24, Soil_Type25, Soil_Type26, Soil_Type27, Soil_Type28, Soil_Type29, Soil_Type30, 
                      Soil_Type31, Soil_Type32, Soil_Type33, Soil_Type34, Soil_Type35, Soil_Type36, Soil_Type37, Soil_Type38, Soil_Type39, Soil_Type40, 
                      Cover_Type);
        */
        if (j != 55)
            done = TRUE;
        else {

            dset->input[i][0] = Elevation_quantitative;
            dset->input[i][1] = Aspect_quantitative;
            dset->input[i][2] = Slope_quantitative;
            dset->input[i][3] = Horizontal_Distance_To_Hydrology_quantitative;
            dset->input[i][4] = Vertical_Distance_To_Hydrology_quantitative;            
            dset->input[i][5] = Horizontal_Distance_To_Roadways_quantitative;            
            dset->input[i][6] = Hillshade_9am_quantitative;            
            dset->input[i][7] = Hillshade_Noon_quantitative;            
            dset->input[i][8] = Hillshade_3pm_quantitative;            
            dset->input[i][9] = Horizontal_Distance_To_Fire_Points_quantitative;            
            dset->input[i][10] = Wilderness_Area_1;                        
            dset->input[i][11] = Wilderness_Area_2;            
            dset->input[i][12] = Wilderness_Area_3;            
            dset->input[i][13] = Wilderness_Area_4;                                    
            dset->input[i][14] = Soil_Type1;                        
            dset->input[i][15] = Soil_Type2;            
            dset->input[i][16] = Soil_Type3;            
            dset->input[i][17] = Soil_Type4;
            dset->input[i][18] = Soil_Type5;                        
            dset->input[i][19] = Soil_Type6;            
            dset->input[i][20] = Soil_Type7; 
            dset->input[i][21] = Soil_Type8;
            dset->input[i][22] = Soil_Type9;            
            dset->input[i][23] = Soil_Type10;
            dset->input[i][24] = Soil_Type11;            
            dset->input[i][25] = Soil_Type12;
            dset->input[i][26] = Soil_Type13;            
            dset->input[i][27] = Soil_Type14;
            dset->input[i][28] = Soil_Type15;            
            dset->input[i][29] = Soil_Type16;
            dset->input[i][30] = Soil_Type17;            
            dset->input[i][31] = Soil_Type18;
            dset->input[i][32] = Soil_Type19;            
            dset->input[i][33] = Soil_Type20;
            dset->input[i][34] = Soil_Type21;            
            dset->input[i][35] = Soil_Type22;
            dset->input[i][36] = Soil_Type23;            
            dset->input[i][37] = Soil_Type24;
            dset->input[i][38] = Soil_Type25;            
            dset->input[i][39] = Soil_Type26;
            dset->input[i][40] = Soil_Type27;            
            dset->input[i][41] = Soil_Type28;
            dset->input[i][42] = Soil_Type29;            
            dset->input[i][43] = Soil_Type30;
            dset->input[i][44] = Soil_Type31;            
            dset->input[i][45] = Soil_Type32;
            dset->input[i][46] = Soil_Type33;            
            dset->input[i][47] = Soil_Type34;
            dset->input[i][48] = Soil_Type35;            
            dset->input[i][49] = Soil_Type36;
            dset->input[i][50] = Soil_Type37;            
            dset->input[i][51] = Soil_Type38;
            dset->input[i][52] = Soil_Type39;            
            dset->input[i][53] = Soil_Type40;        
           
            if (Cover_Type==1) {
                dset->output[i][0] = 0.9;
                dset->output[i][1] = 0.1;
                dset->output[i][2] = 0.1;
                dset->output[i][3] = 0.1;
                dset->output[i][4] = 0.1;
                dset->output[i][5] = 0.1;
                dset->output[i][6] = 0.1;
               
            } else if (Cover_Type==2) {
                dset->output[i][0] = 0.1;
                dset->output[i][1] = 0.9;
                dset->output[i][2] = 0.1;
                dset->output[i][3] = 0.1;
                dset->output[i][4] = 0.1;
                dset->output[i][5] = 0.1;
                dset->output[i][6] = 0.1;
               
            } else if (Cover_Type==3) {
                dset->output[i][0] = 0.1;
                dset->output[i][1] = 0.1;
                dset->output[i][2] = 0.9;
                dset->output[i][3] = 0.1;
                dset->output[i][4] = 0.1;
                dset->output[i][5] = 0.1;
                dset->output[i][6] = 0.1;
               
            } else if (Cover_Type==4) {
                dset->output[i][0] = 0.1;
                dset->output[i][1] = 0.1;
                dset->output[i][2] = 0.1;
                dset->output[i][3] = 0.9;
                dset->output[i][4] = 0.1;
                dset->output[i][5] = 0.1;
                dset->output[i][6] = 0.1;
               
            } else if (Cover_Type==5) {
                dset->output[i][0] = 0.1;
                dset->output[i][1] = 0.9;
                dset->output[i][2] = 0.1;
                dset->output[i][3] = 0.1;
                dset->output[i][4] = 0.9;
                dset->output[i][5] = 0.1;
                dset->output[i][6] = 0.1;
               
            } else if (Cover_Type==6) {
                dset->output[i][0] = 0.1;
                dset->output[i][1] = 0.1;
                dset->output[i][2] = 0.1;
                dset->output[i][3] = 0.1;
                dset->output[i][4] = 0.1;
                dset->output[i][5] = 0.9;
                dset->output[i][6] = 0.1;
               
            } else { 
                dset->output[i][0] = 0.1;
                dset->output[i][1] = 0.1;
                dset->output[i][2] = 0.1;
                dset->output[i][3] = 0.1;
                dset->output[i][4] = 0.1;
                dset->output[i][5] = 0.1;
                dset->output[i][6] = 0.9;
            }
            
            ++i;
        }

    }
//    system("pause");
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

    max = MAX(output[0], MAX(output[1], MAX(output[2], MAX(output[3], MAX(output[4], MAX(output[5], output[6]))))));
    if (output[0] == max)
        return Spruce_Fir;
    else if (output[1] == max)
        return Lodgepole_Pine;
    else if (output[2] == max)
        return Ponderosa_Pine;
    else if (output[3] == max)
        return Cottonwood_Willow;
    else if (output[4] == max)
        return Aspen;
    else if (output[5] == max)
        return Douglas_fir;
    return Krummholz;
}

Class predict_class(Network *nnet, double *input)
{
    forward_prop(nnet, sigmoid, input);
    return output_to_class(nnet->output_layer->y);
}


char    *n1 = "Spruce/Fir";
char    *n2 = "Lodgepole Pine";
char    *n3 = "Ponderosa Pine";
char    *n4 = "Cottonwood/Willow";
char    *n5 = "Aspen";
char    *n6 = "Douglas-fir";
char    *n7 = "Krummholz";

char *class_to_string(Class c)
{
    char *res;
    
    switch(c) {
    case Spruce_Fir:
        res = n1;
        break;
    case Lodgepole_Pine:
        res = n2;
        break;    
    case Ponderosa_Pine:
        res = n3;
        break;
    case Cottonwood_Willow:
        res = n4;
        break;
    case Aspen:
        res = n5;
        break;
    case Douglas_fir:
        res = n6;
        break;    
    default:
        res = n7;
    }

    return res;
}

int main(int argc, char **argv)
{
    int     i;
    int     errors;
    DataSet *train_set;
    DataSet *test_set;
    Network *covtype = create_network(14);
    double  e;
    double  acc;
    Class   predicted, desired;

    // training
    train_set = read_dataset("covtype.train");

    if (train_set == NULL) {
        fprintf(stderr, "Error reading training set\n");
        exit(1);
    }

    add_layer(covtype, 54);  // hidden layer
    add_layer(covtype, 7);  // output layer
    initialize_weights(covtype, SEED);
    print_network_structure(covtype);

    printf("Training network with %d epochs...\n", EPOCHS);
    e = batch_train(covtype, train_set, LEARNING_RATE, EPOCHS,
                    sigmoid, dsigmoid);
    printf("Training finished, approximate final SSE: %f\n", e);

    print_network_structure(covtype);

    // testing
    test_set = read_dataset("covtype.test");

    if (test_set == NULL) {
        fprintf(stderr, "Error reading test set\n");
        exit(1);
    }

    errors = 0;
    printf("Testing with %d cases...\n", test_set->n_cases);
    for (i = 0; i < test_set->n_cases; ++i) {
        predicted = predict_class(covtype, test_set->input[i]);
        desired = output_to_class(test_set->output[i]);
        if (predicted != desired)
            ++errors;
/*        printf("Case %d | predicted: %s, desired: %s, outputs: %4.3f %4.3f \n", i,
               class_to_string(predicted), class_to_string(desired),
               covtype->output_layer->y[0], covtype->output_layer->y[1]);*/
    }

    acc = 100.0 - (100.0 * errors / test_set->n_cases);
    printf("Testing accuracy: %f\n", acc);
    printf("Total classificarion errors: %d\n", errors);
    system("pause");
    return 0;
}
