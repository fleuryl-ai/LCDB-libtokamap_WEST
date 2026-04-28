#ifndef DISTRIBUTIONS_STRUCTURES_H
#define DISTRIBUTIONS_STRUCTURES_H

#include <string>
#include <vector>
#include <complex>

namespace distributions {

// Default initialization values
constexpr int default_value_int = -999999;
constexpr double default_value_double = -9e+40;
constexpr const char* default_value_string = "";

// Structure for thermalization
// Auto-generated structure
struct thermalization_struct {
    double* particles = nullptr;
    double* particles_error_upper = nullptr;
    double* particles_error_lower = nullptr;
    double* power = nullptr;
    double* power_error_upper = nullptr;
    double* power_error_lower = nullptr;
    double* torque = nullptr;
    double* torque_error_upper = nullptr;
    double* torque_error_lower = nullptr;
    double* energy = nullptr;
    int* energy_extents = nullptr;
    int energy_dim = 1;
    double* energy_error_upper = nullptr;
    int* energy_error_upper_extents = nullptr;
    int energy_error_upper_dim = 1;
    double* energy_error_lower = nullptr;
    int* energy_error_lower_extents = nullptr;
    int energy_error_lower_dim = 1;
    double* momentum_phi = nullptr;
    int* momentum_phi_extents = nullptr;
    int momentum_phi_dim = 1;
    double* momentum_phi_error_upper = nullptr;
    int* momentum_phi_error_upper_extents = nullptr;
    int momentum_phi_error_upper_dim = 1;
    double* momentum_phi_error_lower = nullptr;
    int* momentum_phi_error_lower_extents = nullptr;
    int momentum_phi_error_lower_dim = 1;
};

// Structure for vacuum_toroidal_field
// Auto-generated structure
struct vacuum_toroidal_field_struct {
    double* r0 = nullptr;
    double* r0_error_upper = nullptr;
    double* r0_error_lower = nullptr;
    double* b0 = nullptr;
    int* b0_extents = nullptr;
    int b0_dim = 1;
    double* b0_error_upper = nullptr;
    int* b0_error_upper_extents = nullptr;
    int b0_error_upper_dim = 1;
    double* b0_error_lower = nullptr;
    int* b0_error_lower_extents = nullptr;
    int b0_error_lower_dim = 1;
};

// Structure for reactant_energy
// Auto-generated structure
struct reactant_energy_struct {
    std::string name = "";
    int* index = nullptr;
    std::string description = "";
};

// Structure for infrastructure_put
// Auto-generated structure
struct infrastructure_put_struct {
    std::string name = "";
    std::string description = "";
    std::string commit = "";
    std::string version = "";
    std::string repository = "";
};

// Structure for coordinates_type
// Auto-generated structure
struct coordinates_type_struct {
    std::string name = "";
    int* index = nullptr;
    std::string description = "";
};

// Structure for geometry_content
// Auto-generated structure
struct geometry_content_struct {
    std::string name = "";
    int* index = nullptr;
    std::string description = "";
};

// Structure for orbit_integrals
// Auto-generated structure
struct orbit_integrals_struct {
    int* n_phi = nullptr;
    int* n_phi_extents = nullptr;
    int n_phi_dim = 1;
    int* m_pol = nullptr;
    int* m_pol_extents = nullptr;
    int m_pol_dim = 1;
    int* bounce_harmonics = nullptr;
    int* bounce_harmonics_extents = nullptr;
    int bounce_harmonics_dim = 1;
    std::complex<double>* values = nullptr;
    int* values_extents = nullptr;
    int values_dim = 1;
    std::complex<double>* values_error_upper = nullptr;
    int* values_error_upper_extents = nullptr;
    int values_error_upper_dim = 1;
    std::complex<double>* values_error_lower = nullptr;
    int* values_error_lower_extents = nullptr;
    int values_error_lower_dim = 1;
};

// Structure for version_put
// Auto-generated structure
struct version_put_struct {
    std::string data_dictionary = "";
    std::string access_layer = "";
    std::string access_layer_language = "";
};

// Structure for orbit_frequency_tor
// Auto-generated structure
struct orbit_frequency_tor_struct {
    int* grid_index = nullptr;
    int* grid_subset_index = nullptr;
    double* values = nullptr;
    int* values_extents = nullptr;
    int values_dim = 1;
    double* values_error_upper = nullptr;
    int* values_error_upper_extents = nullptr;
    int values_error_upper_dim = 1;
    double* values_error_lower = nullptr;
    int* values_error_lower_extents = nullptr;
    int values_error_lower_dim = 1;
    double* coefficients = nullptr;
    int* coefficients_extents = nullptr;
    int coefficients_dim = 1;
    double* coefficients_error_upper = nullptr;
    int* coefficients_error_upper_extents = nullptr;
    int coefficients_error_upper_dim = 1;
    double* coefficients_error_lower = nullptr;
    int* coefficients_error_lower_extents = nullptr;
    int coefficients_error_lower_dim = 1;
};

// Structure for method
// Auto-generated structure
struct method_struct {
    std::string name = "";
    int* index = nullptr;
    std::string description = "";
};

// Structure for base
// Auto-generated structure
struct base_struct {
    double* jacobian = nullptr;
    int* jacobian_extents = nullptr;
    int jacobian_dim = 1;
    double* jacobian_error_upper = nullptr;
    int* jacobian_error_upper_extents = nullptr;
    int jacobian_error_upper_dim = 1;
    double* jacobian_error_lower = nullptr;
    int* jacobian_error_lower_extents = nullptr;
    int jacobian_error_lower_dim = 1;
    double* tensor_covariant = nullptr;
    int* tensor_covariant_extents = nullptr;
    int tensor_covariant_dim = 1;
    double* tensor_covariant_error_upper = nullptr;
    int* tensor_covariant_error_upper_extents = nullptr;
    int tensor_covariant_error_upper_dim = 1;
    double* tensor_covariant_error_lower = nullptr;
    int* tensor_covariant_error_lower_extents = nullptr;
    int tensor_covariant_error_lower_dim = 1;
    double* tensor_contravariant = nullptr;
    int* tensor_contravariant_extents = nullptr;
    int tensor_contravariant_dim = 1;
    double* tensor_contravariant_error_upper = nullptr;
    int* tensor_contravariant_error_upper_extents = nullptr;
    int tensor_contravariant_error_upper_dim = 1;
    double* tensor_contravariant_error_lower = nullptr;
    int* tensor_contravariant_error_lower_extents = nullptr;
    int tensor_contravariant_error_lower_dim = 1;
};

// Structure for metric
// Auto-generated structure
struct metric_struct {
    double* jacobian = nullptr;
    int* jacobian_extents = nullptr;
    int jacobian_dim = 1;
    double* jacobian_error_upper = nullptr;
    int* jacobian_error_upper_extents = nullptr;
    int jacobian_error_upper_dim = 1;
    double* jacobian_error_lower = nullptr;
    int* jacobian_error_lower_extents = nullptr;
    int jacobian_error_lower_dim = 1;
    double* tensor_covariant = nullptr;
    int* tensor_covariant_extents = nullptr;
    int tensor_covariant_dim = 1;
    double* tensor_covariant_error_upper = nullptr;
    int* tensor_covariant_error_upper_extents = nullptr;
    int tensor_covariant_error_upper_dim = 1;
    double* tensor_covariant_error_lower = nullptr;
    int* tensor_covariant_error_lower_extents = nullptr;
    int tensor_covariant_error_lower_dim = 1;
    double* tensor_contravariant = nullptr;
    int* tensor_contravariant_extents = nullptr;
    int tensor_contravariant_dim = 1;
    double* tensor_contravariant_error_upper = nullptr;
    int* tensor_contravariant_error_upper_extents = nullptr;
    int tensor_contravariant_error_upper_dim = 1;
    double* tensor_contravariant_error_lower = nullptr;
    int* tensor_contravariant_error_lower_extents = nullptr;
    int tensor_contravariant_error_lower_dim = 1;
};

// Structure for boundary
// Auto-generated structure
struct boundary_struct {
    int* index = nullptr;
    int* neighbours = nullptr;
    int* neighbours_extents = nullptr;
    int neighbours_dim = 1;
};

// Structure for occurrence_type
// Auto-generated structure
struct occurrence_type_struct {
    std::string name = "";
    int* index = nullptr;
    std::string description = "";
};

// Structure for library
// Auto-generated structure
struct library_struct {
    std::string name = "";
    std::string description = "";
    std::string commit = "";
    std::string version = "";
    std::string repository = "";
    std::string parameters = "";
};

// Structure for orbit
// Auto-generated structure
struct orbit_struct {
    int* grid_index = nullptr;
    int* grid_subset_index = nullptr;
    double* values = nullptr;
    int* values_extents = nullptr;
    int values_dim = 1;
    double* values_error_upper = nullptr;
    int* values_error_upper_extents = nullptr;
    int values_error_upper_dim = 1;
    double* values_error_lower = nullptr;
    int* values_error_lower_extents = nullptr;
    int values_error_lower_dim = 1;
    double* coefficients = nullptr;
    int* coefficients_extents = nullptr;
    int coefficients_dim = 1;
    double* coefficients_error_upper = nullptr;
    int* coefficients_error_upper_extents = nullptr;
    int coefficients_error_upper_dim = 1;
    double* coefficients_error_lower = nullptr;
    int* coefficients_error_lower_extents = nullptr;
    int coefficients_error_lower_dim = 1;
};

// Structure for electrons
// Auto-generated structure
struct electrons_struct {
    double* power_thermal = nullptr;
    double* power_thermal_error_upper = nullptr;
    double* power_thermal_error_lower = nullptr;
    double* power_fast = nullptr;
    double* power_fast_error_upper = nullptr;
    double* power_fast_error_lower = nullptr;
    double* torque_thermal_phi = nullptr;
    double* torque_thermal_phi_error_upper = nullptr;
    double* torque_thermal_phi_error_lower = nullptr;
    double* torque_fast_phi = nullptr;
    double* torque_fast_phi_error_upper = nullptr;
    double* torque_fast_phi_error_lower = nullptr;
};

// Structure for reference
// Auto-generated structure
struct reference_struct {
    std::string name = "";
    std::string timestamp = "";
};

// Structure for orbit_frequency_pol
// Auto-generated structure
struct orbit_frequency_pol_struct {
    int* grid_index = nullptr;
    int* grid_subset_index = nullptr;
    double* values = nullptr;
    int* values_extents = nullptr;
    int values_dim = 1;
    double* values_error_upper = nullptr;
    int* values_error_upper_extents = nullptr;
    int values_error_upper_dim = 1;
    double* values_error_lower = nullptr;
    int* values_error_lower_extents = nullptr;
    int values_error_lower_dim = 1;
    double* coefficients = nullptr;
    int* coefficients_extents = nullptr;
    int coefficients_dim = 1;
    double* coefficients_error_upper = nullptr;
    int* coefficients_error_upper_extents = nullptr;
    int coefficients_error_upper_dim = 1;
    double* coefficients_error_lower = nullptr;
    int* coefficients_error_lower_extents = nullptr;
    int coefficients_error_lower_dim = 1;
};

// Structure for geometry_type
// Auto-generated structure
struct geometry_type_struct {
    std::string name = "";
    int* index = nullptr;
    std::string description = "";
};

// Structure for neutral_type
// Auto-generated structure
struct neutral_type_struct {
    std::string name = "";
    int* index = nullptr;
    std::string description = "";
};

// Structure for orbit_integrals_instant
// Auto-generated structure
struct orbit_integrals_instant_struct {
    double* time_orbit = nullptr;
    int* time_orbit_extents = nullptr;
    int time_orbit_dim = 1;
    double* time_orbit_error_upper = nullptr;
    int* time_orbit_error_upper_extents = nullptr;
    int time_orbit_error_upper_dim = 1;
    double* time_orbit_error_lower = nullptr;
    int* time_orbit_error_lower_extents = nullptr;
    int time_orbit_error_lower_dim = 1;
    std::complex<double>* values = nullptr;
    int* values_extents = nullptr;
    int values_dim = 1;
    std::complex<double>* values_error_upper = nullptr;
    int* values_error_upper_extents = nullptr;
    int values_error_upper_dim = 1;
    std::complex<double>* values_error_lower = nullptr;
    int* values_error_lower_extents = nullptr;
    int values_error_lower_dim = 1;
};

// Structure for nbi_energy
// Auto-generated structure
struct nbi_energy_struct {
    std::string name = "";
    int* index = nullptr;
    std::string description = "";
};

// Structure for orbit_type
// Auto-generated structure
struct orbit_type_struct {
    int* grid_index = nullptr;
    int* grid_subset_index = nullptr;
    int* values = nullptr;
    int* values_extents = nullptr;
    int values_dim = 1;
};

// Structure for amplitude
// Auto-generated structure
struct amplitude_struct {
    int* grid_index = nullptr;
    int* grid_subset_index = nullptr;
    double* values = nullptr;
    int* values_extents = nullptr;
    int values_dim = 1;
    double* values_error_upper = nullptr;
    int* values_error_upper_extents = nullptr;
    int values_error_upper_dim = 1;
    double* values_error_lower = nullptr;
    int* values_error_lower_extents = nullptr;
    int values_error_lower_dim = 1;
    double* coefficients = nullptr;
    int* coefficients_extents = nullptr;
    int coefficients_dim = 1;
    double* coefficients_error_upper = nullptr;
    int* coefficients_error_upper_extents = nullptr;
    int coefficients_error_upper_dim = 1;
    double* coefficients_error_lower = nullptr;
    int* coefficients_error_lower_extents = nullptr;
    int coefficients_error_lower_dim = 1;
};

// Structure for infrastructure_get
// Auto-generated structure
struct infrastructure_get_struct {
    std::string name = "";
    std::string description = "";
    std::string commit = "";
    std::string version = "";
    std::string repository = "";
};

// Structure for magnetic_axis
// Auto-generated structure
struct magnetic_axis_struct {
    double* r = nullptr;
    int* r_extents = nullptr;
    int r_dim = 1;
    double* r_error_upper = nullptr;
    int* r_error_upper_extents = nullptr;
    int r_error_upper_dim = 1;
    double* r_error_lower = nullptr;
    int* r_error_lower_extents = nullptr;
    int r_error_lower_dim = 1;
    double* z = nullptr;
    int* z_extents = nullptr;
    int z_dim = 1;
    double* z_error_upper = nullptr;
    int* z_error_upper_extents = nullptr;
    int z_error_upper_dim = 1;
    double* z_error_lower = nullptr;
    int* z_error_lower_extents = nullptr;
    int z_error_lower_dim = 1;
};

// Structure for type
// Auto-generated structure
struct type_struct {
    std::string name = "";
    int* index = nullptr;
    std::string description = "";
};

// Structure for coordinate_identifier
// Auto-generated structure
struct coordinate_identifier_struct {
    std::string name = "";
    int* index = nullptr;
    std::string description = "";
};

// Structure for fast_filter
// Auto-generated structure
struct fast_filter_struct {
    method_struct method;
    double* energy = nullptr;
    int* energy_extents = nullptr;
    int energy_dim = 1;
    double* energy_error_upper = nullptr;
    int* energy_error_upper_extents = nullptr;
    int energy_error_upper_dim = 1;
    double* energy_error_lower = nullptr;
    int* energy_error_lower_extents = nullptr;
    int energy_error_lower_dim = 1;
};

// Structure for object
// Auto-generated structure
struct object_struct {
    std::vector<boundary_struct> boundary_vect;
    double* geometry = nullptr;
    int* geometry_extents = nullptr;
    int geometry_dim = 1;
    int* nodes = nullptr;
    int* nodes_extents = nullptr;
    int nodes_dim = 1;
    double* measure = nullptr;
    double* geometry_2d = nullptr;
    int* geometry_2d_extents = nullptr;
    int geometry_2d_dim = 1;
    int* space = nullptr;
    int* dimension = nullptr;
    int* index = nullptr;
};

// Structure for put_operation
// Auto-generated structure
struct put_operation_struct {
    std::string name = "";
    std::string description = "";
    std::string commit = "";
    std::string version = "";
    std::string repository = "";
    std::string parameters = "";
    std::vector<library_struct> library_vect;
};

// Structure for get_operation
// Auto-generated structure
struct get_operation_struct {
    std::string name = "";
    std::string description = "";
    std::string commit = "";
    std::string version = "";
    std::string repository = "";
    std::string parameters = "";
    std::vector<library_struct> library_vect;
};

// Structure for readback
// Auto-generated structure
struct readback_struct {
    std::string name = "";
    std::string description = "";
    std::string commit = "";
    std::string version = "";
    std::string repository = "";
    std::string parameters = "";
    std::vector<library_struct> library_vect;
};

// Structure for code
// Auto-generated structure
struct code_struct {
    std::string name = "";
    std::string description = "";
    std::string commit = "";
    std::string version = "";
    std::string repository = "";
    std::string parameters = "";
    int* output_flag = nullptr;
    int* output_flag_extents = nullptr;
    int output_flag_dim = 1;
    std::vector<library_struct> library_vect;
};

// Structure for state
// Auto-generated structure
struct state_struct {
    double* z_min = nullptr;
    double* z_min_error_upper = nullptr;
    double* z_min_error_lower = nullptr;
    double* z_max = nullptr;
    double* z_max_error_upper = nullptr;
    double* z_max_error_lower = nullptr;
    std::string name = "";
    std::string electron_configuration = "";
    double* vibrational_level = nullptr;
    double* vibrational_level_error_upper = nullptr;
    double* vibrational_level_error_lower = nullptr;
    std::string vibrational_mode = "";
    neutral_type_struct neutral_type;
    double* power_thermal = nullptr;
    double* power_thermal_error_upper = nullptr;
    double* power_thermal_error_lower = nullptr;
    double* power_fast = nullptr;
    double* power_fast_error_upper = nullptr;
    double* power_fast_error_lower = nullptr;
    double* torque_thermal_phi = nullptr;
    double* torque_thermal_phi_error_upper = nullptr;
    double* torque_thermal_phi_error_lower = nullptr;
    double* torque_fast_phi = nullptr;
    double* torque_fast_phi_error_upper = nullptr;
    double* torque_fast_phi_error_lower = nullptr;
    double* torque_fast_tor = nullptr;
    int* torque_fast_tor_extents = nullptr;
    int torque_fast_tor_dim = 1;
    double* torque_fast_tor_error_upper = nullptr;
    int* torque_fast_tor_error_upper_extents = nullptr;
    int torque_fast_tor_error_upper_dim = 1;
    double* torque_fast_tor_error_lower = nullptr;
    int* torque_fast_tor_error_lower_extents = nullptr;
    int torque_fast_tor_error_lower_dim = 1;
};

// Structure for wave
// Auto-generated structure
struct wave_struct {
    type_struct type;
    std::string antenna_name = "";
    int* index_in_antenna = nullptr;
};

// Structure for process
// Auto-generated structure
struct process_struct {
    type_struct type;
    reactant_energy_struct reactant_energy;
    nbi_energy_struct nbi_energy;
    int* nbi_unit = nullptr;
    int* nbi_beamlets_group = nullptr;
};

// Structure for identifier
// Auto-generated structure
struct identifier_struct {
    type_struct type;
    int* wave_index = nullptr;
    int* process_index = nullptr;
    std::string name = "";
    int* index = nullptr;
    std::string description = "";
};

// Structure for markers
// Auto-generated structure
struct markers_struct {
    std::vector<coordinate_identifier_struct> coordinate_identifier_vect;
    double* weights = nullptr;
    int* weights_extents = nullptr;
    int weights_dim = 1;
    double* weights_error_upper = nullptr;
    int* weights_error_upper_extents = nullptr;
    int weights_error_upper_dim = 1;
    double* weights_error_lower = nullptr;
    int* weights_error_lower_extents = nullptr;
    int weights_error_lower_dim = 1;
    double* positions = nullptr;
    int* positions_extents = nullptr;
    int positions_dim = 1;
    double* positions_error_upper = nullptr;
    int* positions_error_upper_extents = nullptr;
    int positions_error_upper_dim = 1;
    double* positions_error_lower = nullptr;
    int* positions_error_lower_extents = nullptr;
    int positions_error_lower_dim = 1;
    orbit_integrals_struct orbit_integrals;
    orbit_integrals_instant_struct orbit_integrals_instant;
    int* toroidal_mode = nullptr;
    double* time = nullptr;
};

// Structure for objects_per_dimension
// Auto-generated structure
struct objects_per_dimension_struct {
    std::vector<object_struct> object_vect;
    geometry_content_struct geometry_content;
};

// Structure for element
// Auto-generated structure
struct element_struct {
    double* a = nullptr;
    double* a_error_upper = nullptr;
    double* a_error_lower = nullptr;
    int* z_n = nullptr;
    int* atoms_n = nullptr;
    std::vector<object_struct> object_vect;
};

// Structure for node
// Auto-generated structure
struct node_struct {
    std::string path = "";
    std::vector<reference_struct> reference_vect;
    std::vector<put_operation_struct> put_operation_vect;
    std::vector<readback_struct> readback_vect;
    std::vector<get_operation_struct> get_operation_vect;
};

// Structure for source
// Auto-generated structure
struct source_struct {
    identifier_struct identifier;
    double* particles = nullptr;
    double* particles_error_upper = nullptr;
    double* particles_error_lower = nullptr;
    double* power = nullptr;
    double* power_error_upper = nullptr;
    double* power_error_lower = nullptr;
    double* torque_phi = nullptr;
    double* torque_phi_error_upper = nullptr;
    double* torque_phi_error_lower = nullptr;
    double* energy = nullptr;
    int* energy_extents = nullptr;
    int energy_dim = 1;
    double* energy_error_upper = nullptr;
    int* energy_error_upper_extents = nullptr;
    int energy_error_upper_dim = 1;
    double* energy_error_lower = nullptr;
    int* energy_error_lower_extents = nullptr;
    int energy_error_lower_dim = 1;
    double* momentum_phi = nullptr;
    int* momentum_phi_extents = nullptr;
    int momentum_phi_dim = 1;
    double* momentum_phi_error_upper = nullptr;
    int* momentum_phi_error_upper_extents = nullptr;
    int momentum_phi_error_upper_dim = 1;
    double* momentum_phi_error_lower = nullptr;
    int* momentum_phi_error_lower_extents = nullptr;
    int momentum_phi_error_lower_dim = 1;
};

// Structure for space
// Auto-generated structure
struct space_struct {
    identifier_struct identifier;
    geometry_type_struct geometry_type;
    std::vector<coordinates_type_struct> coordinates_type_vect;
    std::vector<objects_per_dimension_struct> objects_per_dimension_vect;
};

// Structure for ion
// Auto-generated structure
struct ion_struct {
    std::vector<element_struct> element_vect;
    double* z_ion = nullptr;
    double* z_ion_error_upper = nullptr;
    double* z_ion_error_lower = nullptr;
    std::string name = "";
    state_struct state;
    int* neutral_index = nullptr;
    double* power_thermal = nullptr;
    double* power_thermal_error_upper = nullptr;
    double* power_thermal_error_lower = nullptr;
    double* power_fast = nullptr;
    double* power_fast_error_upper = nullptr;
    double* power_fast_error_lower = nullptr;
    double* torque_thermal_phi = nullptr;
    double* torque_thermal_phi_error_upper = nullptr;
    double* torque_thermal_phi_error_lower = nullptr;
    double* torque_fast_phi = nullptr;
    double* torque_fast_phi_error_upper = nullptr;
    double* torque_fast_phi_error_lower = nullptr;
    int* multiple_states_flag = nullptr;
    std::vector<state_struct> state_vect;
};

// Structure for neutral
// Auto-generated structure
struct neutral_struct {
    std::vector<element_struct> element_vect;
    std::string name = "";
    state_struct state;
};

// Structure for grid_subset
// Auto-generated structure
struct grid_subset_struct {
    identifier_struct identifier;
    int* dimension = nullptr;
    std::vector<element_struct> element_vect;
    std::vector<base_struct> base_vect;
    metric_struct metric;
    int* grid_index = nullptr;
    int* grid_subset_index = nullptr;
    double* values = nullptr;
    int* values_extents = nullptr;
    int values_dim = 1;
    double* values_error_upper = nullptr;
    int* values_error_upper_extents = nullptr;
    int values_error_upper_dim = 1;
    double* values_error_lower = nullptr;
    int* values_error_lower_extents = nullptr;
    int values_error_lower_dim = 1;
    double* coefficients = nullptr;
    int* coefficients_extents = nullptr;
    int coefficients_dim = 1;
    double* coefficients_error_upper = nullptr;
    int* coefficients_error_upper_extents = nullptr;
    int coefficients_error_upper_dim = 1;
    double* coefficients_error_lower = nullptr;
    int* coefficients_error_lower_extents = nullptr;
    int coefficients_error_lower_dim = 1;
};

// Structure for plugins
// Auto-generated structure
struct plugins_struct {
    std::vector<node_struct> node_vect;
    infrastructure_put_struct infrastructure_put;
    infrastructure_get_struct infrastructure_get;
};

// Structure for provenance
// Auto-generated structure
struct provenance_struct {
    std::vector<node_struct> node_vect;
};

// Structure for collisions
// Auto-generated structure
struct collisions_struct {
    electrons_struct electrons;
    std::vector<ion_struct> ion_vect;
};

// Structure for species
// Auto-generated structure
struct species_struct {
    type_struct type;
    ion_struct ion;
    neutral_struct neutral;
};

// Structure for expansion
// Auto-generated structure
struct expansion_struct {
    std::vector<grid_subset_struct> grid_subset_vect;
};

// Structure for expansion_fd3v
// Auto-generated structure
struct expansion_fd3v_struct {
    std::vector<grid_subset_struct> grid_subset_vect;
};

// Structure for grid
// Auto-generated structure
struct grid_struct {
    double* rho_tor_norm = nullptr;
    int* rho_tor_norm_extents = nullptr;
    int rho_tor_norm_dim = 1;
    double* rho_tor_norm_error_upper = nullptr;
    int* rho_tor_norm_error_upper_extents = nullptr;
    int rho_tor_norm_error_upper_dim = 1;
    double* rho_tor_norm_error_lower = nullptr;
    int* rho_tor_norm_error_lower_extents = nullptr;
    int rho_tor_norm_error_lower_dim = 1;
    double* rho_tor = nullptr;
    int* rho_tor_extents = nullptr;
    int rho_tor_dim = 1;
    double* rho_tor_error_upper = nullptr;
    int* rho_tor_error_upper_extents = nullptr;
    int rho_tor_error_upper_dim = 1;
    double* rho_tor_error_lower = nullptr;
    int* rho_tor_error_lower_extents = nullptr;
    int rho_tor_error_lower_dim = 1;
    double* rho_pol_norm = nullptr;
    int* rho_pol_norm_extents = nullptr;
    int rho_pol_norm_dim = 1;
    double* rho_pol_norm_error_upper = nullptr;
    int* rho_pol_norm_error_upper_extents = nullptr;
    int rho_pol_norm_error_upper_dim = 1;
    double* rho_pol_norm_error_lower = nullptr;
    int* rho_pol_norm_error_lower_extents = nullptr;
    int rho_pol_norm_error_lower_dim = 1;
    double* psi = nullptr;
    int* psi_extents = nullptr;
    int psi_dim = 1;
    double* psi_error_upper = nullptr;
    int* psi_error_upper_extents = nullptr;
    int psi_error_upper_dim = 1;
    double* psi_error_lower = nullptr;
    int* psi_error_lower_extents = nullptr;
    int psi_error_lower_dim = 1;
    double* volume = nullptr;
    int* volume_extents = nullptr;
    int volume_dim = 1;
    double* volume_error_upper = nullptr;
    int* volume_error_upper_extents = nullptr;
    int volume_error_upper_dim = 1;
    double* volume_error_lower = nullptr;
    int* volume_error_lower_extents = nullptr;
    int volume_error_lower_dim = 1;
    double* area = nullptr;
    int* area_extents = nullptr;
    int area_dim = 1;
    double* area_error_upper = nullptr;
    int* area_error_upper_extents = nullptr;
    int area_error_upper_dim = 1;
    double* area_error_lower = nullptr;
    int* area_error_lower_extents = nullptr;
    int area_error_lower_dim = 1;
    double* surface = nullptr;
    int* surface_extents = nullptr;
    int surface_dim = 1;
    double* surface_error_upper = nullptr;
    int* surface_error_upper_extents = nullptr;
    int surface_error_upper_dim = 1;
    double* surface_error_lower = nullptr;
    int* surface_error_lower_extents = nullptr;
    int surface_error_lower_dim = 1;
    double* psi_magnetic_axis = nullptr;
    double* psi_magnetic_axis_error_upper = nullptr;
    double* psi_magnetic_axis_error_lower = nullptr;
    double* psi_boundary = nullptr;
    double* psi_boundary_error_upper = nullptr;
    double* psi_boundary_error_lower = nullptr;
    type_struct type;
    double* r = nullptr;
    int* r_extents = nullptr;
    int r_dim = 1;
    double* r_error_upper = nullptr;
    int* r_error_upper_extents = nullptr;
    int r_error_upper_dim = 1;
    double* r_error_lower = nullptr;
    int* r_error_lower_extents = nullptr;
    int r_error_lower_dim = 1;
    double* z = nullptr;
    int* z_extents = nullptr;
    int z_dim = 1;
    double* z_error_upper = nullptr;
    int* z_error_upper_extents = nullptr;
    int z_error_upper_dim = 1;
    double* z_error_lower = nullptr;
    int* z_error_lower_extents = nullptr;
    int z_error_lower_dim = 1;
    double* theta_straight = nullptr;
    int* theta_straight_extents = nullptr;
    int theta_straight_dim = 1;
    double* theta_straight_error_upper = nullptr;
    int* theta_straight_error_upper_extents = nullptr;
    int theta_straight_error_upper_dim = 1;
    double* theta_straight_error_lower = nullptr;
    int* theta_straight_error_lower_extents = nullptr;
    int theta_straight_error_lower_dim = 1;
    double* theta_geometric = nullptr;
    int* theta_geometric_extents = nullptr;
    int theta_geometric_dim = 1;
    double* theta_geometric_error_upper = nullptr;
    int* theta_geometric_error_upper_extents = nullptr;
    int theta_geometric_error_upper_dim = 1;
    double* theta_geometric_error_lower = nullptr;
    int* theta_geometric_error_lower_extents = nullptr;
    int theta_geometric_error_lower_dim = 1;
    identifier_struct identifier;
    std::string path = "";
    std::vector<space_struct> space_vect;
    std::vector<grid_subset_struct> grid_subset_vect;
};

// Structure for ids_properties
// Auto-generated structure
struct ids_properties_struct {
    std::string comment = "";
    std::string name = "";
    int* homogeneous_time = nullptr;
    occurrence_type_struct occurrence_type;
    std::string provider = "";
    std::string creation_date = "";
    version_put_struct version_put;
    provenance_struct provenance;
    plugins_struct plugins;
};

// Structure for counter_passing
// Auto-generated structure
struct counter_passing_struct {
    double* density = nullptr;
    int* density_extents = nullptr;
    int density_dim = 1;
    double* density_error_upper = nullptr;
    int* density_error_upper_extents = nullptr;
    int density_error_upper_dim = 1;
    double* density_error_lower = nullptr;
    int* density_error_lower_extents = nullptr;
    int density_error_lower_dim = 1;
    double* density_fast = nullptr;
    int* density_fast_extents = nullptr;
    int density_fast_dim = 1;
    double* density_fast_error_upper = nullptr;
    int* density_fast_error_upper_extents = nullptr;
    int density_fast_error_upper_dim = 1;
    double* density_fast_error_lower = nullptr;
    int* density_fast_error_lower_extents = nullptr;
    int density_fast_error_lower_dim = 1;
    double* pressure = nullptr;
    int* pressure_extents = nullptr;
    int pressure_dim = 1;
    double* pressure_error_upper = nullptr;
    int* pressure_error_upper_extents = nullptr;
    int pressure_error_upper_dim = 1;
    double* pressure_error_lower = nullptr;
    int* pressure_error_lower_extents = nullptr;
    int pressure_error_lower_dim = 1;
    double* pressure_fast = nullptr;
    int* pressure_fast_extents = nullptr;
    int pressure_fast_dim = 1;
    double* pressure_fast_error_upper = nullptr;
    int* pressure_fast_error_upper_extents = nullptr;
    int pressure_fast_error_upper_dim = 1;
    double* pressure_fast_error_lower = nullptr;
    int* pressure_fast_error_lower_extents = nullptr;
    int pressure_fast_error_lower_dim = 1;
    double* pressure_fast_parallel = nullptr;
    int* pressure_fast_parallel_extents = nullptr;
    int pressure_fast_parallel_dim = 1;
    double* pressure_fast_parallel_error_upper = nullptr;
    int* pressure_fast_parallel_error_upper_extents = nullptr;
    int pressure_fast_parallel_error_upper_dim = 1;
    double* pressure_fast_parallel_error_lower = nullptr;
    int* pressure_fast_parallel_error_lower_extents = nullptr;
    int pressure_fast_parallel_error_lower_dim = 1;
    double* pressure_fast_perpendicular = nullptr;
    int* pressure_fast_perpendicular_extents = nullptr;
    int pressure_fast_perpendicular_dim = 1;
    double* pressure_fast_perpendicular_error_upper = nullptr;
    int* pressure_fast_perpendicular_error_upper_extents = nullptr;
    int pressure_fast_perpendicular_error_upper_dim = 1;
    double* pressure_fast_perpendicular_error_lower = nullptr;
    int* pressure_fast_perpendicular_error_lower_extents = nullptr;
    int pressure_fast_perpendicular_error_lower_dim = 1;
    double* current_phi = nullptr;
    int* current_phi_extents = nullptr;
    int current_phi_dim = 1;
    double* current_phi_error_upper = nullptr;
    int* current_phi_error_upper_extents = nullptr;
    int current_phi_error_upper_dim = 1;
    double* current_phi_error_lower = nullptr;
    int* current_phi_error_lower_extents = nullptr;
    int current_phi_error_lower_dim = 1;
    double* current_fast_phi = nullptr;
    int* current_fast_phi_extents = nullptr;
    int current_fast_phi_dim = 1;
    double* current_fast_phi_error_upper = nullptr;
    int* current_fast_phi_error_upper_extents = nullptr;
    int current_fast_phi_error_upper_dim = 1;
    double* current_fast_phi_error_lower = nullptr;
    int* current_fast_phi_error_lower_extents = nullptr;
    int current_fast_phi_error_lower_dim = 1;
    double* torque_phi_j_radial = nullptr;
    int* torque_phi_j_radial_extents = nullptr;
    int torque_phi_j_radial_dim = 1;
    double* torque_phi_j_radial_error_upper = nullptr;
    int* torque_phi_j_radial_error_upper_extents = nullptr;
    int torque_phi_j_radial_error_upper_dim = 1;
    double* torque_phi_j_radial_error_lower = nullptr;
    int* torque_phi_j_radial_error_lower_extents = nullptr;
    int torque_phi_j_radial_error_lower_dim = 1;
    collisions_struct collisions;
    std::vector<source_struct> source_vect;
};

// Structure for trapped
// Auto-generated structure
struct trapped_struct {
    double* density = nullptr;
    int* density_extents = nullptr;
    int density_dim = 1;
    double* density_error_upper = nullptr;
    int* density_error_upper_extents = nullptr;
    int density_error_upper_dim = 1;
    double* density_error_lower = nullptr;
    int* density_error_lower_extents = nullptr;
    int density_error_lower_dim = 1;
    double* density_fast = nullptr;
    int* density_fast_extents = nullptr;
    int density_fast_dim = 1;
    double* density_fast_error_upper = nullptr;
    int* density_fast_error_upper_extents = nullptr;
    int density_fast_error_upper_dim = 1;
    double* density_fast_error_lower = nullptr;
    int* density_fast_error_lower_extents = nullptr;
    int density_fast_error_lower_dim = 1;
    double* pressure = nullptr;
    int* pressure_extents = nullptr;
    int pressure_dim = 1;
    double* pressure_error_upper = nullptr;
    int* pressure_error_upper_extents = nullptr;
    int pressure_error_upper_dim = 1;
    double* pressure_error_lower = nullptr;
    int* pressure_error_lower_extents = nullptr;
    int pressure_error_lower_dim = 1;
    double* pressure_fast = nullptr;
    int* pressure_fast_extents = nullptr;
    int pressure_fast_dim = 1;
    double* pressure_fast_error_upper = nullptr;
    int* pressure_fast_error_upper_extents = nullptr;
    int pressure_fast_error_upper_dim = 1;
    double* pressure_fast_error_lower = nullptr;
    int* pressure_fast_error_lower_extents = nullptr;
    int pressure_fast_error_lower_dim = 1;
    double* pressure_fast_parallel = nullptr;
    int* pressure_fast_parallel_extents = nullptr;
    int pressure_fast_parallel_dim = 1;
    double* pressure_fast_parallel_error_upper = nullptr;
    int* pressure_fast_parallel_error_upper_extents = nullptr;
    int pressure_fast_parallel_error_upper_dim = 1;
    double* pressure_fast_parallel_error_lower = nullptr;
    int* pressure_fast_parallel_error_lower_extents = nullptr;
    int pressure_fast_parallel_error_lower_dim = 1;
    double* pressure_fast_perpendicular = nullptr;
    int* pressure_fast_perpendicular_extents = nullptr;
    int pressure_fast_perpendicular_dim = 1;
    double* pressure_fast_perpendicular_error_upper = nullptr;
    int* pressure_fast_perpendicular_error_upper_extents = nullptr;
    int pressure_fast_perpendicular_error_upper_dim = 1;
    double* pressure_fast_perpendicular_error_lower = nullptr;
    int* pressure_fast_perpendicular_error_lower_extents = nullptr;
    int pressure_fast_perpendicular_error_lower_dim = 1;
    double* current_phi = nullptr;
    int* current_phi_extents = nullptr;
    int current_phi_dim = 1;
    double* current_phi_error_upper = nullptr;
    int* current_phi_error_upper_extents = nullptr;
    int current_phi_error_upper_dim = 1;
    double* current_phi_error_lower = nullptr;
    int* current_phi_error_lower_extents = nullptr;
    int current_phi_error_lower_dim = 1;
    double* current_fast_phi = nullptr;
    int* current_fast_phi_extents = nullptr;
    int current_fast_phi_dim = 1;
    double* current_fast_phi_error_upper = nullptr;
    int* current_fast_phi_error_upper_extents = nullptr;
    int current_fast_phi_error_upper_dim = 1;
    double* current_fast_phi_error_lower = nullptr;
    int* current_fast_phi_error_lower_extents = nullptr;
    int current_fast_phi_error_lower_dim = 1;
    double* torque_phi_j_radial = nullptr;
    int* torque_phi_j_radial_extents = nullptr;
    int torque_phi_j_radial_dim = 1;
    double* torque_phi_j_radial_error_upper = nullptr;
    int* torque_phi_j_radial_error_upper_extents = nullptr;
    int torque_phi_j_radial_error_upper_dim = 1;
    double* torque_phi_j_radial_error_lower = nullptr;
    int* torque_phi_j_radial_error_lower_extents = nullptr;
    int torque_phi_j_radial_error_lower_dim = 1;
    collisions_struct collisions;
    std::vector<source_struct> source_vect;
};

// Structure for co_passing
// Auto-generated structure
struct co_passing_struct {
    double* density = nullptr;
    int* density_extents = nullptr;
    int density_dim = 1;
    double* density_error_upper = nullptr;
    int* density_error_upper_extents = nullptr;
    int density_error_upper_dim = 1;
    double* density_error_lower = nullptr;
    int* density_error_lower_extents = nullptr;
    int density_error_lower_dim = 1;
    double* density_fast = nullptr;
    int* density_fast_extents = nullptr;
    int density_fast_dim = 1;
    double* density_fast_error_upper = nullptr;
    int* density_fast_error_upper_extents = nullptr;
    int density_fast_error_upper_dim = 1;
    double* density_fast_error_lower = nullptr;
    int* density_fast_error_lower_extents = nullptr;
    int density_fast_error_lower_dim = 1;
    double* pressure = nullptr;
    int* pressure_extents = nullptr;
    int pressure_dim = 1;
    double* pressure_error_upper = nullptr;
    int* pressure_error_upper_extents = nullptr;
    int pressure_error_upper_dim = 1;
    double* pressure_error_lower = nullptr;
    int* pressure_error_lower_extents = nullptr;
    int pressure_error_lower_dim = 1;
    double* pressure_fast = nullptr;
    int* pressure_fast_extents = nullptr;
    int pressure_fast_dim = 1;
    double* pressure_fast_error_upper = nullptr;
    int* pressure_fast_error_upper_extents = nullptr;
    int pressure_fast_error_upper_dim = 1;
    double* pressure_fast_error_lower = nullptr;
    int* pressure_fast_error_lower_extents = nullptr;
    int pressure_fast_error_lower_dim = 1;
    double* pressure_fast_parallel = nullptr;
    int* pressure_fast_parallel_extents = nullptr;
    int pressure_fast_parallel_dim = 1;
    double* pressure_fast_parallel_error_upper = nullptr;
    int* pressure_fast_parallel_error_upper_extents = nullptr;
    int pressure_fast_parallel_error_upper_dim = 1;
    double* pressure_fast_parallel_error_lower = nullptr;
    int* pressure_fast_parallel_error_lower_extents = nullptr;
    int pressure_fast_parallel_error_lower_dim = 1;
    double* pressure_fast_perpendicular = nullptr;
    int* pressure_fast_perpendicular_extents = nullptr;
    int pressure_fast_perpendicular_dim = 1;
    double* pressure_fast_perpendicular_error_upper = nullptr;
    int* pressure_fast_perpendicular_error_upper_extents = nullptr;
    int pressure_fast_perpendicular_error_upper_dim = 1;
    double* pressure_fast_perpendicular_error_lower = nullptr;
    int* pressure_fast_perpendicular_error_lower_extents = nullptr;
    int pressure_fast_perpendicular_error_lower_dim = 1;
    double* current_phi = nullptr;
    int* current_phi_extents = nullptr;
    int current_phi_dim = 1;
    double* current_phi_error_upper = nullptr;
    int* current_phi_error_upper_extents = nullptr;
    int current_phi_error_upper_dim = 1;
    double* current_phi_error_lower = nullptr;
    int* current_phi_error_lower_extents = nullptr;
    int current_phi_error_lower_dim = 1;
    double* current_fast_phi = nullptr;
    int* current_fast_phi_extents = nullptr;
    int current_fast_phi_dim = 1;
    double* current_fast_phi_error_upper = nullptr;
    int* current_fast_phi_error_upper_extents = nullptr;
    int current_fast_phi_error_upper_dim = 1;
    double* current_fast_phi_error_lower = nullptr;
    int* current_fast_phi_error_lower_extents = nullptr;
    int current_fast_phi_error_lower_dim = 1;
    double* torque_phi_j_radial = nullptr;
    int* torque_phi_j_radial_extents = nullptr;
    int torque_phi_j_radial_dim = 1;
    double* torque_phi_j_radial_error_upper = nullptr;
    int* torque_phi_j_radial_error_upper_extents = nullptr;
    int torque_phi_j_radial_error_upper_dim = 1;
    double* torque_phi_j_radial_error_lower = nullptr;
    int* torque_phi_j_radial_error_lower_extents = nullptr;
    int torque_phi_j_radial_error_lower_dim = 1;
    collisions_struct collisions;
    std::vector<source_struct> source_vect;
};

// Structure for global_quantities
// Auto-generated structure
struct global_quantities_struct {
    double* particles_n = nullptr;
    double* particles_n_error_upper = nullptr;
    double* particles_n_error_lower = nullptr;
    double* particles_fast_n = nullptr;
    double* particles_fast_n_error_upper = nullptr;
    double* particles_fast_n_error_lower = nullptr;
    double* energy = nullptr;
    double* energy_error_upper = nullptr;
    double* energy_error_lower = nullptr;
    double* energy_fast = nullptr;
    double* energy_fast_error_upper = nullptr;
    double* energy_fast_error_lower = nullptr;
    double* energy_fast_parallel = nullptr;
    double* energy_fast_parallel_error_upper = nullptr;
    double* energy_fast_parallel_error_lower = nullptr;
    double* torque_tor_j_radial = nullptr;
    double* torque_tor_j_radial_error_upper = nullptr;
    double* torque_tor_j_radial_error_lower = nullptr;
    double* current_phi = nullptr;
    double* current_phi_error_upper = nullptr;
    double* current_phi_error_lower = nullptr;
    double* power_first_orbit = nullptr;
    double* power_first_orbit_error_upper = nullptr;
    double* power_first_orbit_error_lower = nullptr;
    double* power_rotation = nullptr;
    double* power_rotation_error_upper = nullptr;
    double* power_rotation_error_lower = nullptr;
    double* power_charge_exchange = nullptr;
    double* power_charge_exchange_error_upper = nullptr;
    double* power_charge_exchange_error_lower = nullptr;
    collisions_struct collisions;
    thermalization_struct thermalization;
    std::vector<source_struct> source_vect;
    double* time = nullptr;
};

// Structure for ggd
// Auto-generated structure
struct ggd_struct {
    grid_struct grid;
    double* temperature = nullptr;
    int* temperature_extents = nullptr;
    int temperature_dim = 1;
    double* temperature_error_upper = nullptr;
    int* temperature_error_upper_extents = nullptr;
    int temperature_error_upper_dim = 1;
    double* temperature_error_lower = nullptr;
    int* temperature_error_lower_extents = nullptr;
    int temperature_error_lower_dim = 1;
    orbit_frequency_pol_struct orbit_frequency_pol;
    orbit_frequency_tor_struct orbit_frequency_tor;
    std::vector<expansion_struct> expansion_vect;
    std::vector<expansion_fd3v_struct> expansion_fd3v_vect;
    amplitude_struct amplitude;
    orbit_struct orbit;
    orbit_type_struct orbit_type;
    double* time = nullptr;
};

// Structure for profiles_1d
// Auto-generated structure
struct profiles_1d_struct {
    grid_struct grid;
    fast_filter_struct fast_filter;
    double* density = nullptr;
    int* density_extents = nullptr;
    int density_dim = 1;
    double* density_error_upper = nullptr;
    int* density_error_upper_extents = nullptr;
    int density_error_upper_dim = 1;
    double* density_error_lower = nullptr;
    int* density_error_lower_extents = nullptr;
    int density_error_lower_dim = 1;
    double* density_fast = nullptr;
    int* density_fast_extents = nullptr;
    int density_fast_dim = 1;
    double* density_fast_error_upper = nullptr;
    int* density_fast_error_upper_extents = nullptr;
    int density_fast_error_upper_dim = 1;
    double* density_fast_error_lower = nullptr;
    int* density_fast_error_lower_extents = nullptr;
    int density_fast_error_lower_dim = 1;
    double* pressure = nullptr;
    int* pressure_extents = nullptr;
    int pressure_dim = 1;
    double* pressure_error_upper = nullptr;
    int* pressure_error_upper_extents = nullptr;
    int pressure_error_upper_dim = 1;
    double* pressure_error_lower = nullptr;
    int* pressure_error_lower_extents = nullptr;
    int pressure_error_lower_dim = 1;
    double* pressure_fast = nullptr;
    int* pressure_fast_extents = nullptr;
    int pressure_fast_dim = 1;
    double* pressure_fast_error_upper = nullptr;
    int* pressure_fast_error_upper_extents = nullptr;
    int pressure_fast_error_upper_dim = 1;
    double* pressure_fast_error_lower = nullptr;
    int* pressure_fast_error_lower_extents = nullptr;
    int pressure_fast_error_lower_dim = 1;
    double* pressure_fast_parallel = nullptr;
    int* pressure_fast_parallel_extents = nullptr;
    int pressure_fast_parallel_dim = 1;
    double* pressure_fast_parallel_error_upper = nullptr;
    int* pressure_fast_parallel_error_upper_extents = nullptr;
    int pressure_fast_parallel_error_upper_dim = 1;
    double* pressure_fast_parallel_error_lower = nullptr;
    int* pressure_fast_parallel_error_lower_extents = nullptr;
    int pressure_fast_parallel_error_lower_dim = 1;
    double* pressure_fast_perpendicular = nullptr;
    int* pressure_fast_perpendicular_extents = nullptr;
    int pressure_fast_perpendicular_dim = 1;
    double* pressure_fast_perpendicular_error_upper = nullptr;
    int* pressure_fast_perpendicular_error_upper_extents = nullptr;
    int pressure_fast_perpendicular_error_upper_dim = 1;
    double* pressure_fast_perpendicular_error_lower = nullptr;
    int* pressure_fast_perpendicular_error_lower_extents = nullptr;
    int pressure_fast_perpendicular_error_lower_dim = 1;
    double* current_phi = nullptr;
    int* current_phi_extents = nullptr;
    int current_phi_dim = 1;
    double* current_phi_error_upper = nullptr;
    int* current_phi_error_upper_extents = nullptr;
    int current_phi_error_upper_dim = 1;
    double* current_phi_error_lower = nullptr;
    int* current_phi_error_lower_extents = nullptr;
    int current_phi_error_lower_dim = 1;
    double* current_fast_phi = nullptr;
    int* current_fast_phi_extents = nullptr;
    int current_fast_phi_dim = 1;
    double* current_fast_phi_error_upper = nullptr;
    int* current_fast_phi_error_upper_extents = nullptr;
    int current_fast_phi_error_upper_dim = 1;
    double* current_fast_phi_error_lower = nullptr;
    int* current_fast_phi_error_lower_extents = nullptr;
    int current_fast_phi_error_lower_dim = 1;
    double* torque_phi_j_radial = nullptr;
    int* torque_phi_j_radial_extents = nullptr;
    int torque_phi_j_radial_dim = 1;
    double* torque_phi_j_radial_error_upper = nullptr;
    int* torque_phi_j_radial_error_upper_extents = nullptr;
    int torque_phi_j_radial_error_upper_dim = 1;
    double* torque_phi_j_radial_error_lower = nullptr;
    int* torque_phi_j_radial_error_lower_extents = nullptr;
    int torque_phi_j_radial_error_lower_dim = 1;
    collisions_struct collisions;
    thermalization_struct thermalization;
    std::vector<source_struct> source_vect;
    trapped_struct trapped;
    co_passing_struct co_passing;
    counter_passing_struct counter_passing;
    double* time = nullptr;
};

// Structure for profiles_2d
// Auto-generated structure
struct profiles_2d_struct {
    grid_struct grid;
    double* density = nullptr;
    int* density_extents = nullptr;
    int density_dim = 1;
    double* density_error_upper = nullptr;
    int* density_error_upper_extents = nullptr;
    int density_error_upper_dim = 1;
    double* density_error_lower = nullptr;
    int* density_error_lower_extents = nullptr;
    int density_error_lower_dim = 1;
    double* density_fast = nullptr;
    int* density_fast_extents = nullptr;
    int density_fast_dim = 1;
    double* density_fast_error_upper = nullptr;
    int* density_fast_error_upper_extents = nullptr;
    int density_fast_error_upper_dim = 1;
    double* density_fast_error_lower = nullptr;
    int* density_fast_error_lower_extents = nullptr;
    int density_fast_error_lower_dim = 1;
    double* pressure = nullptr;
    int* pressure_extents = nullptr;
    int pressure_dim = 1;
    double* pressure_error_upper = nullptr;
    int* pressure_error_upper_extents = nullptr;
    int pressure_error_upper_dim = 1;
    double* pressure_error_lower = nullptr;
    int* pressure_error_lower_extents = nullptr;
    int pressure_error_lower_dim = 1;
    double* pressure_fast = nullptr;
    int* pressure_fast_extents = nullptr;
    int pressure_fast_dim = 1;
    double* pressure_fast_error_upper = nullptr;
    int* pressure_fast_error_upper_extents = nullptr;
    int pressure_fast_error_upper_dim = 1;
    double* pressure_fast_error_lower = nullptr;
    int* pressure_fast_error_lower_extents = nullptr;
    int pressure_fast_error_lower_dim = 1;
    double* pressure_fast_parallel = nullptr;
    int* pressure_fast_parallel_extents = nullptr;
    int pressure_fast_parallel_dim = 1;
    double* pressure_fast_parallel_error_upper = nullptr;
    int* pressure_fast_parallel_error_upper_extents = nullptr;
    int pressure_fast_parallel_error_upper_dim = 1;
    double* pressure_fast_parallel_error_lower = nullptr;
    int* pressure_fast_parallel_error_lower_extents = nullptr;
    int pressure_fast_parallel_error_lower_dim = 1;
    double* pressure_fast_perpendicular = nullptr;
    int* pressure_fast_perpendicular_extents = nullptr;
    int pressure_fast_perpendicular_dim = 1;
    double* pressure_fast_perpendicular_error_upper = nullptr;
    int* pressure_fast_perpendicular_error_upper_extents = nullptr;
    int pressure_fast_perpendicular_error_upper_dim = 1;
    double* pressure_fast_perpendicular_error_lower = nullptr;
    int* pressure_fast_perpendicular_error_lower_extents = nullptr;
    int pressure_fast_perpendicular_error_lower_dim = 1;
    double* current_phi = nullptr;
    int* current_phi_extents = nullptr;
    int current_phi_dim = 1;
    double* current_phi_error_upper = nullptr;
    int* current_phi_error_upper_extents = nullptr;
    int current_phi_error_upper_dim = 1;
    double* current_phi_error_lower = nullptr;
    int* current_phi_error_lower_extents = nullptr;
    int current_phi_error_lower_dim = 1;
    double* current_fast_phi = nullptr;
    int* current_fast_phi_extents = nullptr;
    int current_fast_phi_dim = 1;
    double* current_fast_phi_error_upper = nullptr;
    int* current_fast_phi_error_upper_extents = nullptr;
    int current_fast_phi_error_upper_dim = 1;
    double* current_fast_phi_error_lower = nullptr;
    int* current_fast_phi_error_lower_extents = nullptr;
    int current_fast_phi_error_lower_dim = 1;
    double* torque_phi_j_radial = nullptr;
    int* torque_phi_j_radial_extents = nullptr;
    int torque_phi_j_radial_dim = 1;
    double* torque_phi_j_radial_error_upper = nullptr;
    int* torque_phi_j_radial_error_upper_extents = nullptr;
    int torque_phi_j_radial_error_upper_dim = 1;
    double* torque_phi_j_radial_error_lower = nullptr;
    int* torque_phi_j_radial_error_lower_extents = nullptr;
    int torque_phi_j_radial_error_lower_dim = 1;
    collisions_struct collisions;
    trapped_struct trapped;
    co_passing_struct co_passing;
    counter_passing_struct counter_passing;
    double* time = nullptr;
};

// Structure for distribution
// Auto-generated structure
struct distribution_struct {
    std::vector<wave_struct> wave_vect;
    std::vector<process_struct> process_vect;
    int* gyro_type = nullptr;
    species_struct species;
    std::vector<global_quantities_struct> global_quantities_vect;
    std::vector<profiles_1d_struct> profiles_1d_vect;
    std::vector<profiles_2d_struct> profiles_2d_vect;
    int* is_delta_f = nullptr;
    std::vector<ggd_struct> ggd_vect;
    std::vector<markers_struct> markers_vect;
};

// Structure for distributions
// Auto-generated structure
struct distributions {
    ids_properties_struct ids_properties;
    std::vector<distribution_struct> distribution_vect;
    vacuum_toroidal_field_struct vacuum_toroidal_field;
    magnetic_axis_struct magnetic_axis;
    code_struct code;
    double* time = nullptr;
    int* time_extents = nullptr;
    int time_dim = 1;
};

} // namespace distributions
#endif // DISTRIBUTIONS_STRUCTURES_H
