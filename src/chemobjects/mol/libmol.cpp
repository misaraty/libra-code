#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "libmol.h"

using namespace boost::python;


namespace libchemobjects{
namespace libmol{


void export_Mol_objects(){


  void (Atom::*expt_save_v1)(boost::property_tree::ptree& pt,std::string path) = &Atom::save;
  void (Atom::*expt_save_v2)(std::string path) = &Atom::save;


  class_<Atom>("Atom",init<Universe&>())
      .def(init<Universe&, boost::python::dict>())
      .def("__copy__", &generic__copy__<Atom>)
      .def("__deepcopy__", &generic__deepcopy__<Atom>)


      // Topology
      .def_readwrite("Atom_id",&Atom::Atom_id)
      .def_readwrite("globAtom_Index",&Atom::globAtom_Index)
      .def_readwrite("locAtom_Index",&Atom::locAtom_Index)
      .def_readwrite("globGroup_Index",&Atom::globGroup_Index)
      .def_readwrite("globMolecule_Index",&Atom::globMolecule_Index)
      .def_readwrite("globAtom_Adjacent_Atoms",&Atom::globAtom_Adjacent_Atoms)

      // Geometry
      .def_readwrite("Atom_RB",&Atom::Atom_RB)
      .def_readwrite("Atom_RB_old",&Atom::Atom_RB_old)
      .def_readwrite("Atom_displ2",&Atom::Atom_displ2)

      // Properties
      .def_readwrite("Atom_element",&Atom::Atom_element)
      .def_readwrite("Atom_atomic_radius",&Atom::Atom_atomic_radius)
      .def_readwrite("Atom_charge",&Atom::Atom_charge)
      .def_readwrite("Atom_electronegativity",&Atom::Atom_electronegativity)

      .def_readwrite("Atom_formal_charge",&Atom::Atom_formal_charge)
      .def_readwrite("Atom_coordination",&Atom::Atom_coordination)
      .def_readwrite("Atom_functional_group",&Atom::Atom_functional_group)
      .def_readwrite("Atom_min_ring_size",&Atom::Atom_min_ring_size)

      // FF types
      .def_readwrite("Atom_ff_type",&Atom::Atom_ff_type)
//      .def_readwrite("Atom_ff_int_type",&Atom::Atom_ff_int_type)
//      .def_readwrite("Atom_is_surface_atom",&Atom::Atom_is_surface_atom)
//      .def_readwrite("Atom_surface_index",&Atom::Atom_surface_index)
//      .def_readwrite("Atom_is_basis_atom",&Atom::Atom_is_basis_atom)
//      .def_readwrite("Atom_is_C60_CT",&Atom::Atom_is_C60_CT)

      .def("set",&Atom::set)
      .def("show_info",&Atom::show_info)
      .def("save",expt_save_v2)
      .def("load",&Atom::load)
  ;

  class_<std::vector<Atom> >("AtomList")
      .def(vector_indexing_suite<std::vector<Atom> >())
  ;

//  def("save",save);
//  def("load",load);



}// export_Atom_objects




#ifdef CYGWIN
BOOST_PYTHON_MODULE(cygmol){
#else
BOOST_PYTHON_MODULE(libmol){
#endif

  // Register converters:
  // See here: https://misspent.wordpress.com/2009/09/27/how-to-write-boost-python-converters/
  //to_python_converter<std::vector<DATA>, VecToList<DATA> >();

//  export_Mathematics_objects();
  export_Mol_objects();

}


}// namespace libmol
}// namespace libchemobjects



