#include "data_handler.h"

data_handler::data_handler(){
    data_array =        new std::vector<data *>;
    test_data =         new std::vector<data *>;
    traning_data =      new std::vector<data *>;
    validation_data =   new std::vector<data *>;
}

data_handler::~data_handler()
{
    // Free Daynamically Allocated stuff
}

void data_handler::read_feature_vector(std::string path){
    uint32_t header[4];     // MAGIC | NUM IMAGES | ROWSIZE | COLSIZE
    unsigned char bytes[4];
    FILE *f = fopen(path.c_str(), "r");
    if(f){
        for (int i=0; i<4; i++){
            if(fread(bytes, sizeof(bytes), 1, f)){
                header[i] = convert_to_little_endian(bytes);
            }
        }
        printf("Done getting Input file header.\n");
        int image_size = header[2]*header[3];
        for (int i=0; i<header[i]; i++){
            data* d = new data();
            uint8_t element[1];
            for(int j=0; j<image_size; j++){
                if(fread(element, sizeof(element), 1, f)){
                    d->append_to_feature_vector(element[0]);
                }else{
                    printf("Error Reading From File.\n");
                    exit(1);
                }
            }
            data_array->push_back(d);
        }
        printf("Successfully read and stored %lu feature vectors.\n", data_array->size());
    } else{
        printf("Could not find File.\n");
        exit(1);
    }
}

void data_handler::read_feature_labels(std::string path){
    uint32_t header[2];     // MAGIC | NUM IMAGES |
    unsigned char bytes[2];
    FILE *f = fopen(path.c_str(), "r");
    if(f){
        for (int i=0; i<2; i++){
            if(fread(bytes, sizeof(bytes), 1, f)){
                header[i] = convert_to_little_endian(bytes);
            }
        }
        printf("Done getting Label file header.\n");
        for (int i=0; i<header[i]; i++){

            uint8_t element[1];
            if(fread(element, sizeof(element), 1, f)){
                data_array->at(i)->set_label(element[0]);
            }else {
                printf("Error Reading From File.\n");
                exit(1);
            }
        }
        printf("Successfully read and stored %lu Label.\n", data_array->size());
    } else {
        printf("Could not find File.\n");
        exit(1);
    }
}