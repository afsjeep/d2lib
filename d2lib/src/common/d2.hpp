#ifndef _D2_H_
#define _D2_H_

#include <vector>
#include <string>
#include <istream>
#include <ostream>

namespace d2 {

  /* this defines the float point that will be used to 
   * store real numbers.
   */
  typedef float real_t;

  /* this defines the unsigned integer type that will
   * be used to store index 
   */
  typedef unsigned index_t;



  template <typename D2Type>
  struct d2 {
    /* this defines the dimension of supports */
    size_t dim;
    /* this defines the length of supports */
    size_t len;    
    /* this defined the weight array of supports*/
    real_t* w;
    /* this defines the support arrays */
    D2Type* supp;
  };

  template <typename D2Type1, typename D2Type2>
  inline real_t GetDistance( const d2<D2Type1>& op1, 
			     const d2<D2Type2>& op2, 
			     real_t* cache) {
    // to be implement
    return 0.f;
  }

  template <typename D2Type>
  std::istream& operator>> (std::istream& is, d2<D2Type> & op) {
    return is;
  }

  template <typename D2Type>
  std::ostream& operator<< (std::ostream& os, const d2<D2Type> &op) {
    return os;
  }


  template <typename D2Type>
  class d2_block {
  public:
    d2_block(const size_t thesize, const size_t thelen): size(thesize), len(thelen) {
      // allocate mem
    };
    std::vector< d2<D2Type> > vec;    
    
    /* get specific d2 in the block */
    inline d2<D2Type> operator[](size_t ind) const {return vec[ind];}

  private:
    size_t dim, size;
    size_t len, max_len;
    size_t col, max_col;

    std::string type;

    /* actual binary data */
    real_t *p_w;
    D2Type* p_supp;

  };

  template <typename D2Type>
  class mult_d2_block {
  public:
    size_t size;
    std::vector< index_t > label;
    std::vector< d2_block<D2Type> > phase;

    mult_d2_block(const size_t n, 
		  const int* len_arr,
		  const size_t num_of_phases = 1)
      : size(n) {      
      for (int i=0; i<num_of_phases; ++i) {
	phase.push_back( d2_block<D2Type>(n, len_arr[i]) );
	label.resize(n);
      }
    };

    /* file io */
    void read(std::string filename, size_t size);
    void write(std::string filename);


    void write_split(std::string filename);    
  };


}

#endif /* _D2_H_ */