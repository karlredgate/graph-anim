
struct darray {
    void ** data;
    unsigned int entries;
    unsigned int used;
};

typedef struct darray darray;
