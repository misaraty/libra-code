#ifndef LIBMMATH_H
#define LIBMMATH_H

//namespace libmmath{
// Building options define of comment these lines depending on external libraries availability
//#include "libmmathConfig.h"

#include "Units.h"

#include "CMATRIX.h"
#include "DATA.h"                                  
#include "GRAPH.h"                                 
#include "MATRIX.h"                                
#include "MATRIX3x3.h"                             
#include "QUATERNION.h"                            
#include "random.h"                                
#include "SMATRIX.h"                               
#include "SpecialFunctions.h"                      
#include "VECTOR.h" 
                               
#include "Timer.h"
#include "PyCopy.h"
#include "Utility.h"


typedef std::vector<int> intList;
typedef std::vector<float> floatList;
typedef std::vector<double> doubleList;
typedef std::vector<std::complex<double> > complexList;


void export_Mathematics_objects();


//#ifdef USE_EIGEN
//#include "mmath_eigen/eigen.h"
//#endif
//#include "cmatrix.h"

//}

#endif // LIBMMATH_H

