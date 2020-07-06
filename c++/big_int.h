

class big_int {
  public:
    big_int();
    ~big_int();
    void expand();
    void set_uint(unsigned);
    void to_string(char* buf, unsigned max_chars);
    void print();
    big_int operator + (big_int const &);
    //big_int operator == (big_int const &obj);
    //big_int operator = (big_int const &obj);

  private:
    int size; //number of currently allocated segments
    unsigned char* segments;//pointer to segments
};
