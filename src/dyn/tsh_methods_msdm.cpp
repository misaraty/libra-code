/*********************************************************************************
* Copyright (C) 2018 Alexey V. Akimov
*
* This file is distributed under the terms of the GNU General Public License
* as published by the Free Software Foundation, either version 2 of
* the License, or (at your option) any later version.
* See the file LICENSE in the root directory of this distribution
* or <http://www.gnu.org/licenses/>.
*
*********************************************************************************/
/**
  \file tsh_methods_msdm.cpp
  \brief The file implements the modified simplified decay of mixing (MSDM) algorithm. 
    
*/

#include "Surface_Hopping.h"
#include "Energy_and_Forces.h"

/// liblibra namespace
namespace liblibra{

/// libdyn namespace
namespace libdyn{



CMATRIX msdm(CMATRIX& Coeff, double dt, int act_st, MATRIX& decoh_rates){
    /**
    \brief Modified Simplified Decay of Mixing (MSDM) method.
    This function implements the experimental modification (by Alexey Akimov) of the simplified decay of 
    mixing algorithm for decoherence correction ( Granucci, G.; Persico, M. J. Chem. Phys. 2007, 126, 134114)
    
    \param[in]       Coeff [ CMATRIX ] An object containig electronic DOFs. 
    \param[in]          dt [ float ] The integration timestep. Units = a.u. of time
    \param[in]      act_st [ integer ] The active state index
    \param[in]      decoh_rates [ MATRIX ] The matrix of decoherence (pure dephasing) rates between all pairs of states

    The function returns:
    # C [ CMATRIX ] - the updated state of the electronic DOF, in the same data type as the input

    */

    double kb = 3.166811429e-6;  // Hartree/K
    double sclf;

    CMATRIX C(Coeff);
    // First - update all the coefficients for the non-active states        
    int N = Coeff.n_elts;
    for(int i = 0; i<N; i++){
      if(i != act_st){
        double itau = decoh_rates.get(i, act_st); 
        sclf = exp(-dt*itau);
        C.scale(i, 0, sclf);
      }
    }

    // Population of the active state
    double p_aa_old = (std::conj(C.get(act_st,act_st)) * C.get(act_st,act_st)).real();

    // the total population of all inactive states after rescaling
    double new_norm = (C.H() * C).get(0,0).real() - p_aa_old; 
    double p_aa_new = 1.0 - new_norm;

    sclf = 1.0;
    if(p_aa_old > 0.0){
      sclf = sqrt( p_aa_new / p_aa_old );  // scaling factor for the active state
    }
        
    // Rescale the active state
    C.scale(act_st, 0, sclf);
        
    return C;

}


Electronic msdm(Electronic& Coeff, double dt, int act_st, MATRIX& decoh_rates){
    /**
    \brief Modified Simplified Decay of Mixing (MSDM) method.
    This function implements the experimental modification (by Alexey Akimov) of the simplified decay of 
    mixing algorithm for decoherence correction ( Granucci, G.; Persico, M. J. Chem. Phys. 2007, 126, 134114)
    
    \param[in]       Coeff [ Electronic ] An object containig electronic DOFs. 
    \param[in]          dt [ float ] The integration timestep. Units = a.u. of time
    \param[in]      act_st [ integer ] The active state index
    \param[in]      decoh_rates [ MATRIX ] The matrix of decoherence (pure dephasing) rates between all pairs of states

    The function returns:
    # C [ Electronic ] - the updated state of the electronic DOF, in the same data type as the input

    */

    double kb = 3.166811429e-6;  // Hartree/K
    double sclf;

    Electronic C(Coeff);

    // First - update all the coefficients for the non-active states        
    int N = C.nstates;
    double new_norm = 0.0;
    for(int i = 0; i<N; i++){
      if(i != act_st){
        double itau = decoh_rates.get(i, act_st); 
        sclf = exp(-dt*itau);

        C.q[i] = C.q[i] * sclf;
        C.p[i] = C.p[i] * sclf;

        new_norm += C.rho(i, i).real();

      }
    }

    // new_norm now contains the total population of all inactive states after rescaling
    // How much of population is left for the new active state
    double p_aa_new = 1.0 - new_norm;
    double p_aa_old = C.rho(act_st,act_st).real();

    sclf = 1.0;
    if(p_aa_old > 0.0){
      sclf = sqrt( p_aa_new / p_aa_old );  // scaling factor for the active state
    }
        
    // Rescale the active state
    C.q[act_st] = C.q[act_st] * sclf;
    C.p[act_st] = C.p[act_st] * sclf;

    return C;

}




}// namespace libdyn
}// liblibra

