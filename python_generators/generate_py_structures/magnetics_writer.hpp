#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <stdexcept>
#include "NDData.hpp"

/**
 * Auto-generated base class for writing magnetics data to JSON.
 *
 * To use this, create a derived class and override the protected virtual methods
 * to provide real data.
 *
 * Example:
 *
 * class MyMagneticsJsonWriter : public MagneticsJsonWriter {
 * protected:
 *     size_t get_flux_loop() override {
 *         // Return actual size of flux_loop array
 *         return 3;
 *     }
 *
 *     std::string get_flux_loop_name(size_t idx_0) override {
 *         // Return actual name for flux_loop at index idx_0
 *         return "real_name_" + std::to_string(idx_0);
 *     }
 *     // ... override other methods
 * };
 *
 */
class MagneticsJsonWriter
{
public:
    virtual ~MagneticsJsonWriter() = default;

    nlohmann::json generate(int shot)
    {
        nlohmann::json root;

            size_t size_b_field_phi_probe = get_b_field_phi_probe();
            for (size_t idx_0 = 0; idx_0 < size_b_field_phi_probe; ++idx_0) {
                root["b_field_phi_probe"][idx_0]["area"] = get_b_field_phi_probe_area(idx_0);
                root["b_field_phi_probe"][idx_0]["area_error_lower"] = get_b_field_phi_probe_area_error_lower(idx_0);
                root["b_field_phi_probe"][idx_0]["area_error_upper"] = get_b_field_phi_probe_area_error_upper(idx_0);
                root["b_field_phi_probe"][idx_0]["bandwidth_3db"] = get_b_field_phi_probe_bandwidth_3db(idx_0);
                root["b_field_phi_probe"][idx_0]["bandwidth_3db_error_lower"] = get_b_field_phi_probe_bandwidth_3db_error_lower(idx_0);
                root["b_field_phi_probe"][idx_0]["bandwidth_3db_error_upper"] = get_b_field_phi_probe_bandwidth_3db_error_upper(idx_0);
                root["b_field_phi_probe"][idx_0]["description"] = get_b_field_phi_probe_description(idx_0);
                root["b_field_phi_probe"][idx_0]["field"]["data"] = get_b_field_phi_probe_field_data(idx_0);
                root["b_field_phi_probe"][idx_0]["field"]["data_error_lower"] = get_b_field_phi_probe_field_data_error_lower(idx_0);
                root["b_field_phi_probe"][idx_0]["field"]["data_error_upper"] = get_b_field_phi_probe_field_data_error_upper(idx_0);
                root["b_field_phi_probe"][idx_0]["field"]["time"] = get_b_field_phi_probe_field_time(idx_0);
                root["b_field_phi_probe"][idx_0]["field"]["validity"] = get_b_field_phi_probe_field_validity(idx_0);
                root["b_field_phi_probe"][idx_0]["field"]["validity_timed"] = get_b_field_phi_probe_field_validity_timed(idx_0);
                root["b_field_phi_probe"][idx_0]["indices_differential"] = get_b_field_phi_probe_indices_differential(idx_0);
                root["b_field_phi_probe"][idx_0]["length"] = get_b_field_phi_probe_length(idx_0);
                root["b_field_phi_probe"][idx_0]["length_error_lower"] = get_b_field_phi_probe_length_error_lower(idx_0);
                root["b_field_phi_probe"][idx_0]["length_error_upper"] = get_b_field_phi_probe_length_error_upper(idx_0);
                root["b_field_phi_probe"][idx_0]["name"] = get_b_field_phi_probe_name(idx_0);
                root["b_field_phi_probe"][idx_0]["non_linear_response"]["b_field_linear"] = get_b_field_phi_probe_non_linear_response_b_field_linear(idx_0);
                root["b_field_phi_probe"][idx_0]["non_linear_response"]["b_field_linear_error_lower"] = get_b_field_phi_probe_non_linear_response_b_field_linear_error_lower(idx_0);
                root["b_field_phi_probe"][idx_0]["non_linear_response"]["b_field_linear_error_upper"] = get_b_field_phi_probe_non_linear_response_b_field_linear_error_upper(idx_0);
                root["b_field_phi_probe"][idx_0]["non_linear_response"]["b_field_non_linear"] = get_b_field_phi_probe_non_linear_response_b_field_non_linear(idx_0);
                root["b_field_phi_probe"][idx_0]["non_linear_response"]["b_field_non_linear_error_lower"] = get_b_field_phi_probe_non_linear_response_b_field_non_linear_error_lower(idx_0);
                root["b_field_phi_probe"][idx_0]["non_linear_response"]["b_field_non_linear_error_upper"] = get_b_field_phi_probe_non_linear_response_b_field_non_linear_error_upper(idx_0);
                root["b_field_phi_probe"][idx_0]["poloidal_angle"] = get_b_field_phi_probe_poloidal_angle(idx_0);
                root["b_field_phi_probe"][idx_0]["poloidal_angle_error_lower"] = get_b_field_phi_probe_poloidal_angle_error_lower(idx_0);
                root["b_field_phi_probe"][idx_0]["poloidal_angle_error_upper"] = get_b_field_phi_probe_poloidal_angle_error_upper(idx_0);
                root["b_field_phi_probe"][idx_0]["position"]["first_point"]["r"] = get_b_field_phi_probe_position_first_point_r(idx_0);
                root["b_field_phi_probe"][idx_0]["position"]["first_point"]["r_error_lower"] = get_b_field_phi_probe_position_first_point_r_error_lower(idx_0);
                root["b_field_phi_probe"][idx_0]["position"]["first_point"]["r_error_upper"] = get_b_field_phi_probe_position_first_point_r_error_upper(idx_0);
                root["b_field_phi_probe"][idx_0]["position"]["first_point"]["z"] = get_b_field_phi_probe_position_first_point_z(idx_0);
                root["b_field_phi_probe"][idx_0]["position"]["first_point"]["z_error_lower"] = get_b_field_phi_probe_position_first_point_z_error_lower(idx_0);
                root["b_field_phi_probe"][idx_0]["position"]["first_point"]["z_error_upper"] = get_b_field_phi_probe_position_first_point_z_error_upper(idx_0);
                root["b_field_phi_probe"][idx_0]["position"]["phi"] = get_b_field_phi_probe_position_phi(idx_0);
                root["b_field_phi_probe"][idx_0]["position"]["phi_error_lower"] = get_b_field_phi_probe_position_phi_error_lower(idx_0);
                root["b_field_phi_probe"][idx_0]["position"]["phi_error_upper"] = get_b_field_phi_probe_position_phi_error_upper(idx_0);
                root["b_field_phi_probe"][idx_0]["position"]["r"] = get_b_field_phi_probe_position_r(idx_0);
                root["b_field_phi_probe"][idx_0]["position"]["r_error_lower"] = get_b_field_phi_probe_position_r_error_lower(idx_0);
                root["b_field_phi_probe"][idx_0]["position"]["r_error_upper"] = get_b_field_phi_probe_position_r_error_upper(idx_0);
                root["b_field_phi_probe"][idx_0]["position"]["second_point"]["r"] = get_b_field_phi_probe_position_second_point_r(idx_0);
                root["b_field_phi_probe"][idx_0]["position"]["second_point"]["r_error_lower"] = get_b_field_phi_probe_position_second_point_r_error_lower(idx_0);
                root["b_field_phi_probe"][idx_0]["position"]["second_point"]["r_error_upper"] = get_b_field_phi_probe_position_second_point_r_error_upper(idx_0);
                root["b_field_phi_probe"][idx_0]["position"]["second_point"]["z"] = get_b_field_phi_probe_position_second_point_z(idx_0);
                root["b_field_phi_probe"][idx_0]["position"]["second_point"]["z_error_lower"] = get_b_field_phi_probe_position_second_point_z_error_lower(idx_0);
                root["b_field_phi_probe"][idx_0]["position"]["second_point"]["z_error_upper"] = get_b_field_phi_probe_position_second_point_z_error_upper(idx_0);
                root["b_field_phi_probe"][idx_0]["position"]["z"] = get_b_field_phi_probe_position_z(idx_0);
                root["b_field_phi_probe"][idx_0]["position"]["z_error_lower"] = get_b_field_phi_probe_position_z_error_lower(idx_0);
                root["b_field_phi_probe"][idx_0]["position"]["z_error_upper"] = get_b_field_phi_probe_position_z_error_upper(idx_0);
                root["b_field_phi_probe"][idx_0]["toroidal_angle"] = get_b_field_phi_probe_toroidal_angle(idx_0);
                root["b_field_phi_probe"][idx_0]["toroidal_angle_error_lower"] = get_b_field_phi_probe_toroidal_angle_error_lower(idx_0);
                root["b_field_phi_probe"][idx_0]["toroidal_angle_error_upper"] = get_b_field_phi_probe_toroidal_angle_error_upper(idx_0);
                root["b_field_phi_probe"][idx_0]["turns"] = get_b_field_phi_probe_turns(idx_0);
                root["b_field_phi_probe"][idx_0]["type"]["description"] = get_b_field_phi_probe_type_description(idx_0);
                root["b_field_phi_probe"][idx_0]["type"]["index"] = get_b_field_phi_probe_type_index(idx_0);
                root["b_field_phi_probe"][idx_0]["type"]["name"] = get_b_field_phi_probe_type_name(idx_0);
                root["b_field_phi_probe"][idx_0]["voltage"]["data"] = get_b_field_phi_probe_voltage_data(idx_0);
                root["b_field_phi_probe"][idx_0]["voltage"]["data_error_lower"] = get_b_field_phi_probe_voltage_data_error_lower(idx_0);
                root["b_field_phi_probe"][idx_0]["voltage"]["data_error_upper"] = get_b_field_phi_probe_voltage_data_error_upper(idx_0);
                root["b_field_phi_probe"][idx_0]["voltage"]["time"] = get_b_field_phi_probe_voltage_time(idx_0);
                root["b_field_phi_probe"][idx_0]["voltage"]["validity"] = get_b_field_phi_probe_voltage_validity(idx_0);
                root["b_field_phi_probe"][idx_0]["voltage"]["validity_timed"] = get_b_field_phi_probe_voltage_validity_timed(idx_0);
            }
            size_t size_b_field_pol_probe = get_b_field_pol_probe();
            for (size_t idx_0 = 0; idx_0 < size_b_field_pol_probe; ++idx_0) {
                root["b_field_pol_probe"][idx_0]["area"] = get_b_field_pol_probe_area(idx_0);
                root["b_field_pol_probe"][idx_0]["area_error_lower"] = get_b_field_pol_probe_area_error_lower(idx_0);
                root["b_field_pol_probe"][idx_0]["area_error_upper"] = get_b_field_pol_probe_area_error_upper(idx_0);
                root["b_field_pol_probe"][idx_0]["bandwidth_3db"] = get_b_field_pol_probe_bandwidth_3db(idx_0);
                root["b_field_pol_probe"][idx_0]["bandwidth_3db_error_lower"] = get_b_field_pol_probe_bandwidth_3db_error_lower(idx_0);
                root["b_field_pol_probe"][idx_0]["bandwidth_3db_error_upper"] = get_b_field_pol_probe_bandwidth_3db_error_upper(idx_0);
                root["b_field_pol_probe"][idx_0]["description"] = get_b_field_pol_probe_description(idx_0);
                root["b_field_pol_probe"][idx_0]["field"]["data"] = get_b_field_pol_probe_field_data(idx_0);
                root["b_field_pol_probe"][idx_0]["field"]["data_error_lower"] = get_b_field_pol_probe_field_data_error_lower(idx_0);
                root["b_field_pol_probe"][idx_0]["field"]["data_error_upper"] = get_b_field_pol_probe_field_data_error_upper(idx_0);
                root["b_field_pol_probe"][idx_0]["field"]["time"] = get_b_field_pol_probe_field_time(idx_0);
                root["b_field_pol_probe"][idx_0]["field"]["validity"] = get_b_field_pol_probe_field_validity(idx_0);
                root["b_field_pol_probe"][idx_0]["field"]["validity_timed"] = get_b_field_pol_probe_field_validity_timed(idx_0);
                root["b_field_pol_probe"][idx_0]["indices_differential"] = get_b_field_pol_probe_indices_differential(idx_0);
                root["b_field_pol_probe"][idx_0]["length"] = get_b_field_pol_probe_length(idx_0);
                root["b_field_pol_probe"][idx_0]["length_error_lower"] = get_b_field_pol_probe_length_error_lower(idx_0);
                root["b_field_pol_probe"][idx_0]["length_error_upper"] = get_b_field_pol_probe_length_error_upper(idx_0);
                root["b_field_pol_probe"][idx_0]["name"] = get_b_field_pol_probe_name(idx_0);
                root["b_field_pol_probe"][idx_0]["non_linear_response"]["b_field_linear"] = get_b_field_pol_probe_non_linear_response_b_field_linear(idx_0);
                root["b_field_pol_probe"][idx_0]["non_linear_response"]["b_field_linear_error_lower"] = get_b_field_pol_probe_non_linear_response_b_field_linear_error_lower(idx_0);
                root["b_field_pol_probe"][idx_0]["non_linear_response"]["b_field_linear_error_upper"] = get_b_field_pol_probe_non_linear_response_b_field_linear_error_upper(idx_0);
                root["b_field_pol_probe"][idx_0]["non_linear_response"]["b_field_non_linear"] = get_b_field_pol_probe_non_linear_response_b_field_non_linear(idx_0);
                root["b_field_pol_probe"][idx_0]["non_linear_response"]["b_field_non_linear_error_lower"] = get_b_field_pol_probe_non_linear_response_b_field_non_linear_error_lower(idx_0);
                root["b_field_pol_probe"][idx_0]["non_linear_response"]["b_field_non_linear_error_upper"] = get_b_field_pol_probe_non_linear_response_b_field_non_linear_error_upper(idx_0);
                root["b_field_pol_probe"][idx_0]["poloidal_angle"] = get_b_field_pol_probe_poloidal_angle(idx_0);
                root["b_field_pol_probe"][idx_0]["poloidal_angle_error_lower"] = get_b_field_pol_probe_poloidal_angle_error_lower(idx_0);
                root["b_field_pol_probe"][idx_0]["poloidal_angle_error_upper"] = get_b_field_pol_probe_poloidal_angle_error_upper(idx_0);
                root["b_field_pol_probe"][idx_0]["position"]["first_point"]["r"] = get_b_field_pol_probe_position_first_point_r(idx_0);
                root["b_field_pol_probe"][idx_0]["position"]["first_point"]["r_error_lower"] = get_b_field_pol_probe_position_first_point_r_error_lower(idx_0);
                root["b_field_pol_probe"][idx_0]["position"]["first_point"]["r_error_upper"] = get_b_field_pol_probe_position_first_point_r_error_upper(idx_0);
                root["b_field_pol_probe"][idx_0]["position"]["first_point"]["z"] = get_b_field_pol_probe_position_first_point_z(idx_0);
                root["b_field_pol_probe"][idx_0]["position"]["first_point"]["z_error_lower"] = get_b_field_pol_probe_position_first_point_z_error_lower(idx_0);
                root["b_field_pol_probe"][idx_0]["position"]["first_point"]["z_error_upper"] = get_b_field_pol_probe_position_first_point_z_error_upper(idx_0);
                root["b_field_pol_probe"][idx_0]["position"]["phi"] = get_b_field_pol_probe_position_phi(idx_0);
                root["b_field_pol_probe"][idx_0]["position"]["phi_error_lower"] = get_b_field_pol_probe_position_phi_error_lower(idx_0);
                root["b_field_pol_probe"][idx_0]["position"]["phi_error_upper"] = get_b_field_pol_probe_position_phi_error_upper(idx_0);
                root["b_field_pol_probe"][idx_0]["position"]["r"] = get_b_field_pol_probe_position_r(idx_0);
                root["b_field_pol_probe"][idx_0]["position"]["r_error_lower"] = get_b_field_pol_probe_position_r_error_lower(idx_0);
                root["b_field_pol_probe"][idx_0]["position"]["r_error_upper"] = get_b_field_pol_probe_position_r_error_upper(idx_0);
                root["b_field_pol_probe"][idx_0]["position"]["second_point"]["r"] = get_b_field_pol_probe_position_second_point_r(idx_0);
                root["b_field_pol_probe"][idx_0]["position"]["second_point"]["r_error_lower"] = get_b_field_pol_probe_position_second_point_r_error_lower(idx_0);
                root["b_field_pol_probe"][idx_0]["position"]["second_point"]["r_error_upper"] = get_b_field_pol_probe_position_second_point_r_error_upper(idx_0);
                root["b_field_pol_probe"][idx_0]["position"]["second_point"]["z"] = get_b_field_pol_probe_position_second_point_z(idx_0);
                root["b_field_pol_probe"][idx_0]["position"]["second_point"]["z_error_lower"] = get_b_field_pol_probe_position_second_point_z_error_lower(idx_0);
                root["b_field_pol_probe"][idx_0]["position"]["second_point"]["z_error_upper"] = get_b_field_pol_probe_position_second_point_z_error_upper(idx_0);
                root["b_field_pol_probe"][idx_0]["position"]["z"] = get_b_field_pol_probe_position_z(idx_0);
                root["b_field_pol_probe"][idx_0]["position"]["z_error_lower"] = get_b_field_pol_probe_position_z_error_lower(idx_0);
                root["b_field_pol_probe"][idx_0]["position"]["z_error_upper"] = get_b_field_pol_probe_position_z_error_upper(idx_0);
                root["b_field_pol_probe"][idx_0]["toroidal_angle"] = get_b_field_pol_probe_toroidal_angle(idx_0);
                root["b_field_pol_probe"][idx_0]["toroidal_angle_error_lower"] = get_b_field_pol_probe_toroidal_angle_error_lower(idx_0);
                root["b_field_pol_probe"][idx_0]["toroidal_angle_error_upper"] = get_b_field_pol_probe_toroidal_angle_error_upper(idx_0);
                root["b_field_pol_probe"][idx_0]["turns"] = get_b_field_pol_probe_turns(idx_0);
                root["b_field_pol_probe"][idx_0]["type"]["description"] = get_b_field_pol_probe_type_description(idx_0);
                root["b_field_pol_probe"][idx_0]["type"]["index"] = get_b_field_pol_probe_type_index(idx_0);
                root["b_field_pol_probe"][idx_0]["type"]["name"] = get_b_field_pol_probe_type_name(idx_0);
                root["b_field_pol_probe"][idx_0]["voltage"]["data"] = get_b_field_pol_probe_voltage_data(idx_0);
                root["b_field_pol_probe"][idx_0]["voltage"]["data_error_lower"] = get_b_field_pol_probe_voltage_data_error_lower(idx_0);
                root["b_field_pol_probe"][idx_0]["voltage"]["data_error_upper"] = get_b_field_pol_probe_voltage_data_error_upper(idx_0);
                root["b_field_pol_probe"][idx_0]["voltage"]["time"] = get_b_field_pol_probe_voltage_time(idx_0);
                root["b_field_pol_probe"][idx_0]["voltage"]["validity"] = get_b_field_pol_probe_voltage_validity(idx_0);
                root["b_field_pol_probe"][idx_0]["voltage"]["validity_timed"] = get_b_field_pol_probe_voltage_validity_timed(idx_0);
            }
            root["b_field_pol_probe_equivalent"] = get_b_field_pol_probe_equivalent();
            root["code"]["commit"] = get_code_commit();
            root["code"]["description"] = get_code_description();
            size_t size_code_library = get_code_library();
            for (size_t idx_0 = 0; idx_0 < size_code_library; ++idx_0) {
                root["code"]["library"][idx_0]["commit"] = get_code_library_commit(idx_0);
                root["code"]["library"][idx_0]["description"] = get_code_library_description(idx_0);
                root["code"]["library"][idx_0]["name"] = get_code_library_name(idx_0);
                root["code"]["library"][idx_0]["parameters"] = get_code_library_parameters(idx_0);
                root["code"]["library"][idx_0]["repository"] = get_code_library_repository(idx_0);
                root["code"]["library"][idx_0]["version"] = get_code_library_version(idx_0);
            }
            root["code"]["name"] = get_code_name();
            root["code"]["output_flag"] = get_code_output_flag();
            root["code"]["parameters"] = get_code_parameters();
            root["code"]["repository"] = get_code_repository();
            root["code"]["version"] = get_code_version();
            size_t size_diamagnetic_flux = get_diamagnetic_flux();
            for (size_t idx_0 = 0; idx_0 < size_diamagnetic_flux; ++idx_0) {
                root["diamagnetic_flux"][idx_0]["data"] = get_diamagnetic_flux_data(idx_0);
                root["diamagnetic_flux"][idx_0]["data_error_lower"] = get_diamagnetic_flux_data_error_lower(idx_0);
                root["diamagnetic_flux"][idx_0]["data_error_upper"] = get_diamagnetic_flux_data_error_upper(idx_0);
                root["diamagnetic_flux"][idx_0]["method_name"] = get_diamagnetic_flux_method_name(idx_0);
                root["diamagnetic_flux"][idx_0]["time"] = get_diamagnetic_flux_time(idx_0);
            }
            size_t size_flux_loop = get_flux_loop();
            for (size_t idx_0 = 0; idx_0 < size_flux_loop; ++idx_0) {
                root["flux_loop"][idx_0]["area"] = get_flux_loop_area(idx_0);
                root["flux_loop"][idx_0]["area_error_lower"] = get_flux_loop_area_error_lower(idx_0);
                root["flux_loop"][idx_0]["area_error_upper"] = get_flux_loop_area_error_upper(idx_0);
                root["flux_loop"][idx_0]["description"] = get_flux_loop_description(idx_0);
                root["flux_loop"][idx_0]["flux"]["data"] = get_flux_loop_flux_data(idx_0);
                root["flux_loop"][idx_0]["flux"]["data_error_lower"] = get_flux_loop_flux_data_error_lower(idx_0);
                root["flux_loop"][idx_0]["flux"]["data_error_upper"] = get_flux_loop_flux_data_error_upper(idx_0);
                root["flux_loop"][idx_0]["flux"]["time"] = get_flux_loop_flux_time(idx_0);
                root["flux_loop"][idx_0]["flux"]["validity"] = get_flux_loop_flux_validity(idx_0);
                root["flux_loop"][idx_0]["flux"]["validity_timed"] = get_flux_loop_flux_validity_timed(idx_0);
                root["flux_loop"][idx_0]["gm9"] = get_flux_loop_gm9(idx_0);
                root["flux_loop"][idx_0]["gm9_error_lower"] = get_flux_loop_gm9_error_lower(idx_0);
                root["flux_loop"][idx_0]["gm9_error_upper"] = get_flux_loop_gm9_error_upper(idx_0);
                root["flux_loop"][idx_0]["indices_differential"] = get_flux_loop_indices_differential(idx_0);
                root["flux_loop"][idx_0]["name"] = get_flux_loop_name(idx_0);
                size_t size_flux_loop_position = get_flux_loop_position(idx_0);
                for (size_t idx_1 = 0; idx_1 < size_flux_loop_position; ++idx_1) {
                    root["flux_loop"][idx_0]["position"][idx_1]["first_point"]["r"] = get_flux_loop_position_first_point_r(idx_0, idx_1);
                    root["flux_loop"][idx_0]["position"][idx_1]["first_point"]["r_error_lower"] = get_flux_loop_position_first_point_r_error_lower(idx_0, idx_1);
                    root["flux_loop"][idx_0]["position"][idx_1]["first_point"]["r_error_upper"] = get_flux_loop_position_first_point_r_error_upper(idx_0, idx_1);
                    root["flux_loop"][idx_0]["position"][idx_1]["first_point"]["z"] = get_flux_loop_position_first_point_z(idx_0, idx_1);
                    root["flux_loop"][idx_0]["position"][idx_1]["first_point"]["z_error_lower"] = get_flux_loop_position_first_point_z_error_lower(idx_0, idx_1);
                    root["flux_loop"][idx_0]["position"][idx_1]["first_point"]["z_error_upper"] = get_flux_loop_position_first_point_z_error_upper(idx_0, idx_1);
                    root["flux_loop"][idx_0]["position"][idx_1]["phi"] = get_flux_loop_position_phi(idx_0, idx_1);
                    root["flux_loop"][idx_0]["position"][idx_1]["phi_error_lower"] = get_flux_loop_position_phi_error_lower(idx_0, idx_1);
                    root["flux_loop"][idx_0]["position"][idx_1]["phi_error_upper"] = get_flux_loop_position_phi_error_upper(idx_0, idx_1);
                    root["flux_loop"][idx_0]["position"][idx_1]["r"] = get_flux_loop_position_r(idx_0, idx_1);
                    root["flux_loop"][idx_0]["position"][idx_1]["r_error_lower"] = get_flux_loop_position_r_error_lower(idx_0, idx_1);
                    root["flux_loop"][idx_0]["position"][idx_1]["r_error_upper"] = get_flux_loop_position_r_error_upper(idx_0, idx_1);
                    root["flux_loop"][idx_0]["position"][idx_1]["second_point"]["r"] = get_flux_loop_position_second_point_r(idx_0, idx_1);
                    root["flux_loop"][idx_0]["position"][idx_1]["second_point"]["r_error_lower"] = get_flux_loop_position_second_point_r_error_lower(idx_0, idx_1);
                    root["flux_loop"][idx_0]["position"][idx_1]["second_point"]["r_error_upper"] = get_flux_loop_position_second_point_r_error_upper(idx_0, idx_1);
                    root["flux_loop"][idx_0]["position"][idx_1]["second_point"]["z"] = get_flux_loop_position_second_point_z(idx_0, idx_1);
                    root["flux_loop"][idx_0]["position"][idx_1]["second_point"]["z_error_lower"] = get_flux_loop_position_second_point_z_error_lower(idx_0, idx_1);
                    root["flux_loop"][idx_0]["position"][idx_1]["second_point"]["z_error_upper"] = get_flux_loop_position_second_point_z_error_upper(idx_0, idx_1);
                    root["flux_loop"][idx_0]["position"][idx_1]["z"] = get_flux_loop_position_z(idx_0, idx_1);
                    root["flux_loop"][idx_0]["position"][idx_1]["z_error_lower"] = get_flux_loop_position_z_error_lower(idx_0, idx_1);
                    root["flux_loop"][idx_0]["position"][idx_1]["z_error_upper"] = get_flux_loop_position_z_error_upper(idx_0, idx_1);
                }
                root["flux_loop"][idx_0]["type"]["description"] = get_flux_loop_type_description(idx_0);
                root["flux_loop"][idx_0]["type"]["index"] = get_flux_loop_type_index(idx_0);
                root["flux_loop"][idx_0]["type"]["name"] = get_flux_loop_type_name(idx_0);
                root["flux_loop"][idx_0]["voltage"]["data"] = get_flux_loop_voltage_data(idx_0);
                root["flux_loop"][idx_0]["voltage"]["data_error_lower"] = get_flux_loop_voltage_data_error_lower(idx_0);
                root["flux_loop"][idx_0]["voltage"]["data_error_upper"] = get_flux_loop_voltage_data_error_upper(idx_0);
                root["flux_loop"][idx_0]["voltage"]["time"] = get_flux_loop_voltage_time(idx_0);
                root["flux_loop"][idx_0]["voltage"]["validity"] = get_flux_loop_voltage_validity(idx_0);
                root["flux_loop"][idx_0]["voltage"]["validity_timed"] = get_flux_loop_voltage_validity_timed(idx_0);
            }
            root["ids_properties"]["comment"] = get_ids_properties_comment();
            root["ids_properties"]["creation_date"] = get_ids_properties_creation_date();
            root["ids_properties"]["homogeneous_time"] = get_ids_properties_homogeneous_time();
            root["ids_properties"]["name"] = get_ids_properties_name();
            root["ids_properties"]["occurrence_type"]["description"] = get_ids_properties_occurrence_type_description();
            root["ids_properties"]["occurrence_type"]["index"] = get_ids_properties_occurrence_type_index();
            root["ids_properties"]["occurrence_type"]["name"] = get_ids_properties_occurrence_type_name();
            root["ids_properties"]["plugins"]["infrastructure_get"]["commit"] = get_ids_properties_plugins_infrastructure_get_commit();
            root["ids_properties"]["plugins"]["infrastructure_get"]["description"] = get_ids_properties_plugins_infrastructure_get_description();
            root["ids_properties"]["plugins"]["infrastructure_get"]["name"] = get_ids_properties_plugins_infrastructure_get_name();
            root["ids_properties"]["plugins"]["infrastructure_get"]["repository"] = get_ids_properties_plugins_infrastructure_get_repository();
            root["ids_properties"]["plugins"]["infrastructure_get"]["version"] = get_ids_properties_plugins_infrastructure_get_version();
            root["ids_properties"]["plugins"]["infrastructure_put"]["commit"] = get_ids_properties_plugins_infrastructure_put_commit();
            root["ids_properties"]["plugins"]["infrastructure_put"]["description"] = get_ids_properties_plugins_infrastructure_put_description();
            root["ids_properties"]["plugins"]["infrastructure_put"]["name"] = get_ids_properties_plugins_infrastructure_put_name();
            root["ids_properties"]["plugins"]["infrastructure_put"]["repository"] = get_ids_properties_plugins_infrastructure_put_repository();
            root["ids_properties"]["plugins"]["infrastructure_put"]["version"] = get_ids_properties_plugins_infrastructure_put_version();
            size_t size_ids_properties_plugins_node = get_ids_properties_plugins_node();
            for (size_t idx_0 = 0; idx_0 < size_ids_properties_plugins_node; ++idx_0) {
                size_t size_ids_properties_plugins_node_get_operation = get_ids_properties_plugins_node_get_operation(idx_0);
                for (size_t idx_1 = 0; idx_1 < size_ids_properties_plugins_node_get_operation; ++idx_1) {
                    root["ids_properties"]["plugins"]["node"][idx_0]["get_operation"][idx_1]["commit"] = get_ids_properties_plugins_node_get_operation_commit(idx_0, idx_1);
                    root["ids_properties"]["plugins"]["node"][idx_0]["get_operation"][idx_1]["description"] = get_ids_properties_plugins_node_get_operation_description(idx_0, idx_1);
                    size_t size_ids_properties_plugins_node_get_operation_library = get_ids_properties_plugins_node_get_operation_library(idx_0, idx_1);
                    for (size_t idx_2 = 0; idx_2 < size_ids_properties_plugins_node_get_operation_library; ++idx_2) {
                        root["ids_properties"]["plugins"]["node"][idx_0]["get_operation"][idx_1]["library"][idx_2]["commit"] = get_ids_properties_plugins_node_get_operation_library_commit(idx_0, idx_1, idx_2);
                        root["ids_properties"]["plugins"]["node"][idx_0]["get_operation"][idx_1]["library"][idx_2]["description"] = get_ids_properties_plugins_node_get_operation_library_description(idx_0, idx_1, idx_2);
                        root["ids_properties"]["plugins"]["node"][idx_0]["get_operation"][idx_1]["library"][idx_2]["name"] = get_ids_properties_plugins_node_get_operation_library_name(idx_0, idx_1, idx_2);
                        root["ids_properties"]["plugins"]["node"][idx_0]["get_operation"][idx_1]["library"][idx_2]["parameters"] = get_ids_properties_plugins_node_get_operation_library_parameters(idx_0, idx_1, idx_2);
                        root["ids_properties"]["plugins"]["node"][idx_0]["get_operation"][idx_1]["library"][idx_2]["repository"] = get_ids_properties_plugins_node_get_operation_library_repository(idx_0, idx_1, idx_2);
                        root["ids_properties"]["plugins"]["node"][idx_0]["get_operation"][idx_1]["library"][idx_2]["version"] = get_ids_properties_plugins_node_get_operation_library_version(idx_0, idx_1, idx_2);
                    }
                    root["ids_properties"]["plugins"]["node"][idx_0]["get_operation"][idx_1]["name"] = get_ids_properties_plugins_node_get_operation_name(idx_0, idx_1);
                    root["ids_properties"]["plugins"]["node"][idx_0]["get_operation"][idx_1]["parameters"] = get_ids_properties_plugins_node_get_operation_parameters(idx_0, idx_1);
                    root["ids_properties"]["plugins"]["node"][idx_0]["get_operation"][idx_1]["repository"] = get_ids_properties_plugins_node_get_operation_repository(idx_0, idx_1);
                    root["ids_properties"]["plugins"]["node"][idx_0]["get_operation"][idx_1]["version"] = get_ids_properties_plugins_node_get_operation_version(idx_0, idx_1);
                }
                root["ids_properties"]["plugins"]["node"][idx_0]["path"] = get_ids_properties_plugins_node_path(idx_0);
                size_t size_ids_properties_plugins_node_put_operation = get_ids_properties_plugins_node_put_operation(idx_0);
                for (size_t idx_1 = 0; idx_1 < size_ids_properties_plugins_node_put_operation; ++idx_1) {
                    root["ids_properties"]["plugins"]["node"][idx_0]["put_operation"][idx_1]["commit"] = get_ids_properties_plugins_node_put_operation_commit(idx_0, idx_1);
                    root["ids_properties"]["plugins"]["node"][idx_0]["put_operation"][idx_1]["description"] = get_ids_properties_plugins_node_put_operation_description(idx_0, idx_1);
                    size_t size_ids_properties_plugins_node_put_operation_library = get_ids_properties_plugins_node_put_operation_library(idx_0, idx_1);
                    for (size_t idx_2 = 0; idx_2 < size_ids_properties_plugins_node_put_operation_library; ++idx_2) {
                        root["ids_properties"]["plugins"]["node"][idx_0]["put_operation"][idx_1]["library"][idx_2]["commit"] = get_ids_properties_plugins_node_put_operation_library_commit(idx_0, idx_1, idx_2);
                        root["ids_properties"]["plugins"]["node"][idx_0]["put_operation"][idx_1]["library"][idx_2]["description"] = get_ids_properties_plugins_node_put_operation_library_description(idx_0, idx_1, idx_2);
                        root["ids_properties"]["plugins"]["node"][idx_0]["put_operation"][idx_1]["library"][idx_2]["name"] = get_ids_properties_plugins_node_put_operation_library_name(idx_0, idx_1, idx_2);
                        root["ids_properties"]["plugins"]["node"][idx_0]["put_operation"][idx_1]["library"][idx_2]["parameters"] = get_ids_properties_plugins_node_put_operation_library_parameters(idx_0, idx_1, idx_2);
                        root["ids_properties"]["plugins"]["node"][idx_0]["put_operation"][idx_1]["library"][idx_2]["repository"] = get_ids_properties_plugins_node_put_operation_library_repository(idx_0, idx_1, idx_2);
                        root["ids_properties"]["plugins"]["node"][idx_0]["put_operation"][idx_1]["library"][idx_2]["version"] = get_ids_properties_plugins_node_put_operation_library_version(idx_0, idx_1, idx_2);
                    }
                    root["ids_properties"]["plugins"]["node"][idx_0]["put_operation"][idx_1]["name"] = get_ids_properties_plugins_node_put_operation_name(idx_0, idx_1);
                    root["ids_properties"]["plugins"]["node"][idx_0]["put_operation"][idx_1]["parameters"] = get_ids_properties_plugins_node_put_operation_parameters(idx_0, idx_1);
                    root["ids_properties"]["plugins"]["node"][idx_0]["put_operation"][idx_1]["repository"] = get_ids_properties_plugins_node_put_operation_repository(idx_0, idx_1);
                    root["ids_properties"]["plugins"]["node"][idx_0]["put_operation"][idx_1]["version"] = get_ids_properties_plugins_node_put_operation_version(idx_0, idx_1);
                }
                size_t size_ids_properties_plugins_node_readback = get_ids_properties_plugins_node_readback(idx_0);
                for (size_t idx_1 = 0; idx_1 < size_ids_properties_plugins_node_readback; ++idx_1) {
                    root["ids_properties"]["plugins"]["node"][idx_0]["readback"][idx_1]["commit"] = get_ids_properties_plugins_node_readback_commit(idx_0, idx_1);
                    root["ids_properties"]["plugins"]["node"][idx_0]["readback"][idx_1]["description"] = get_ids_properties_plugins_node_readback_description(idx_0, idx_1);
                    size_t size_ids_properties_plugins_node_readback_library = get_ids_properties_plugins_node_readback_library(idx_0, idx_1);
                    for (size_t idx_2 = 0; idx_2 < size_ids_properties_plugins_node_readback_library; ++idx_2) {
                        root["ids_properties"]["plugins"]["node"][idx_0]["readback"][idx_1]["library"][idx_2]["commit"] = get_ids_properties_plugins_node_readback_library_commit(idx_0, idx_1, idx_2);
                        root["ids_properties"]["plugins"]["node"][idx_0]["readback"][idx_1]["library"][idx_2]["description"] = get_ids_properties_plugins_node_readback_library_description(idx_0, idx_1, idx_2);
                        root["ids_properties"]["plugins"]["node"][idx_0]["readback"][idx_1]["library"][idx_2]["name"] = get_ids_properties_plugins_node_readback_library_name(idx_0, idx_1, idx_2);
                        root["ids_properties"]["plugins"]["node"][idx_0]["readback"][idx_1]["library"][idx_2]["parameters"] = get_ids_properties_plugins_node_readback_library_parameters(idx_0, idx_1, idx_2);
                        root["ids_properties"]["plugins"]["node"][idx_0]["readback"][idx_1]["library"][idx_2]["repository"] = get_ids_properties_plugins_node_readback_library_repository(idx_0, idx_1, idx_2);
                        root["ids_properties"]["plugins"]["node"][idx_0]["readback"][idx_1]["library"][idx_2]["version"] = get_ids_properties_plugins_node_readback_library_version(idx_0, idx_1, idx_2);
                    }
                    root["ids_properties"]["plugins"]["node"][idx_0]["readback"][idx_1]["name"] = get_ids_properties_plugins_node_readback_name(idx_0, idx_1);
                    root["ids_properties"]["plugins"]["node"][idx_0]["readback"][idx_1]["parameters"] = get_ids_properties_plugins_node_readback_parameters(idx_0, idx_1);
                    root["ids_properties"]["plugins"]["node"][idx_0]["readback"][idx_1]["repository"] = get_ids_properties_plugins_node_readback_repository(idx_0, idx_1);
                    root["ids_properties"]["plugins"]["node"][idx_0]["readback"][idx_1]["version"] = get_ids_properties_plugins_node_readback_version(idx_0, idx_1);
                }
                size_t size_ids_properties_plugins_node_reference = get_ids_properties_plugins_node_reference(idx_0);
                for (size_t idx_1 = 0; idx_1 < size_ids_properties_plugins_node_reference; ++idx_1) {
                    root["ids_properties"]["plugins"]["node"][idx_0]["reference"][idx_1]["name"] = get_ids_properties_plugins_node_reference_name(idx_0, idx_1);
                    root["ids_properties"]["plugins"]["node"][idx_0]["reference"][idx_1]["timestamp"] = get_ids_properties_plugins_node_reference_timestamp(idx_0, idx_1);
                }
            }
            size_t size_ids_properties_provenance_node = get_ids_properties_provenance_node();
            for (size_t idx_0 = 0; idx_0 < size_ids_properties_provenance_node; ++idx_0) {
                size_t size_ids_properties_provenance_node_get_operation = get_ids_properties_provenance_node_get_operation(idx_0);
                for (size_t idx_1 = 0; idx_1 < size_ids_properties_provenance_node_get_operation; ++idx_1) {
                    root["ids_properties"]["provenance"]["node"][idx_0]["get_operation"][idx_1]["commit"] = get_ids_properties_provenance_node_get_operation_commit(idx_0, idx_1);
                    root["ids_properties"]["provenance"]["node"][idx_0]["get_operation"][idx_1]["description"] = get_ids_properties_provenance_node_get_operation_description(idx_0, idx_1);
                    size_t size_ids_properties_provenance_node_get_operation_library = get_ids_properties_provenance_node_get_operation_library(idx_0, idx_1);
                    for (size_t idx_2 = 0; idx_2 < size_ids_properties_provenance_node_get_operation_library; ++idx_2) {
                        root["ids_properties"]["provenance"]["node"][idx_0]["get_operation"][idx_1]["library"][idx_2]["commit"] = get_ids_properties_provenance_node_get_operation_library_commit(idx_0, idx_1, idx_2);
                        root["ids_properties"]["provenance"]["node"][idx_0]["get_operation"][idx_1]["library"][idx_2]["description"] = get_ids_properties_provenance_node_get_operation_library_description(idx_0, idx_1, idx_2);
                        root["ids_properties"]["provenance"]["node"][idx_0]["get_operation"][idx_1]["library"][idx_2]["name"] = get_ids_properties_provenance_node_get_operation_library_name(idx_0, idx_1, idx_2);
                        root["ids_properties"]["provenance"]["node"][idx_0]["get_operation"][idx_1]["library"][idx_2]["parameters"] = get_ids_properties_provenance_node_get_operation_library_parameters(idx_0, idx_1, idx_2);
                        root["ids_properties"]["provenance"]["node"][idx_0]["get_operation"][idx_1]["library"][idx_2]["repository"] = get_ids_properties_provenance_node_get_operation_library_repository(idx_0, idx_1, idx_2);
                        root["ids_properties"]["provenance"]["node"][idx_0]["get_operation"][idx_1]["library"][idx_2]["version"] = get_ids_properties_provenance_node_get_operation_library_version(idx_0, idx_1, idx_2);
                    }
                    root["ids_properties"]["provenance"]["node"][idx_0]["get_operation"][idx_1]["name"] = get_ids_properties_provenance_node_get_operation_name(idx_0, idx_1);
                    root["ids_properties"]["provenance"]["node"][idx_0]["get_operation"][idx_1]["parameters"] = get_ids_properties_provenance_node_get_operation_parameters(idx_0, idx_1);
                    root["ids_properties"]["provenance"]["node"][idx_0]["get_operation"][idx_1]["repository"] = get_ids_properties_provenance_node_get_operation_repository(idx_0, idx_1);
                    root["ids_properties"]["provenance"]["node"][idx_0]["get_operation"][idx_1]["version"] = get_ids_properties_provenance_node_get_operation_version(idx_0, idx_1);
                }
                root["ids_properties"]["provenance"]["node"][idx_0]["path"] = get_ids_properties_provenance_node_path(idx_0);
                size_t size_ids_properties_provenance_node_put_operation = get_ids_properties_provenance_node_put_operation(idx_0);
                for (size_t idx_1 = 0; idx_1 < size_ids_properties_provenance_node_put_operation; ++idx_1) {
                    root["ids_properties"]["provenance"]["node"][idx_0]["put_operation"][idx_1]["commit"] = get_ids_properties_provenance_node_put_operation_commit(idx_0, idx_1);
                    root["ids_properties"]["provenance"]["node"][idx_0]["put_operation"][idx_1]["description"] = get_ids_properties_provenance_node_put_operation_description(idx_0, idx_1);
                    size_t size_ids_properties_provenance_node_put_operation_library = get_ids_properties_provenance_node_put_operation_library(idx_0, idx_1);
                    for (size_t idx_2 = 0; idx_2 < size_ids_properties_provenance_node_put_operation_library; ++idx_2) {
                        root["ids_properties"]["provenance"]["node"][idx_0]["put_operation"][idx_1]["library"][idx_2]["commit"] = get_ids_properties_provenance_node_put_operation_library_commit(idx_0, idx_1, idx_2);
                        root["ids_properties"]["provenance"]["node"][idx_0]["put_operation"][idx_1]["library"][idx_2]["description"] = get_ids_properties_provenance_node_put_operation_library_description(idx_0, idx_1, idx_2);
                        root["ids_properties"]["provenance"]["node"][idx_0]["put_operation"][idx_1]["library"][idx_2]["name"] = get_ids_properties_provenance_node_put_operation_library_name(idx_0, idx_1, idx_2);
                        root["ids_properties"]["provenance"]["node"][idx_0]["put_operation"][idx_1]["library"][idx_2]["parameters"] = get_ids_properties_provenance_node_put_operation_library_parameters(idx_0, idx_1, idx_2);
                        root["ids_properties"]["provenance"]["node"][idx_0]["put_operation"][idx_1]["library"][idx_2]["repository"] = get_ids_properties_provenance_node_put_operation_library_repository(idx_0, idx_1, idx_2);
                        root["ids_properties"]["provenance"]["node"][idx_0]["put_operation"][idx_1]["library"][idx_2]["version"] = get_ids_properties_provenance_node_put_operation_library_version(idx_0, idx_1, idx_2);
                    }
                    root["ids_properties"]["provenance"]["node"][idx_0]["put_operation"][idx_1]["name"] = get_ids_properties_provenance_node_put_operation_name(idx_0, idx_1);
                    root["ids_properties"]["provenance"]["node"][idx_0]["put_operation"][idx_1]["parameters"] = get_ids_properties_provenance_node_put_operation_parameters(idx_0, idx_1);
                    root["ids_properties"]["provenance"]["node"][idx_0]["put_operation"][idx_1]["repository"] = get_ids_properties_provenance_node_put_operation_repository(idx_0, idx_1);
                    root["ids_properties"]["provenance"]["node"][idx_0]["put_operation"][idx_1]["version"] = get_ids_properties_provenance_node_put_operation_version(idx_0, idx_1);
                }
                size_t size_ids_properties_provenance_node_readback = get_ids_properties_provenance_node_readback(idx_0);
                for (size_t idx_1 = 0; idx_1 < size_ids_properties_provenance_node_readback; ++idx_1) {
                    root["ids_properties"]["provenance"]["node"][idx_0]["readback"][idx_1]["commit"] = get_ids_properties_provenance_node_readback_commit(idx_0, idx_1);
                    root["ids_properties"]["provenance"]["node"][idx_0]["readback"][idx_1]["description"] = get_ids_properties_provenance_node_readback_description(idx_0, idx_1);
                    size_t size_ids_properties_provenance_node_readback_library = get_ids_properties_provenance_node_readback_library(idx_0, idx_1);
                    for (size_t idx_2 = 0; idx_2 < size_ids_properties_provenance_node_readback_library; ++idx_2) {
                        root["ids_properties"]["provenance"]["node"][idx_0]["readback"][idx_1]["library"][idx_2]["commit"] = get_ids_properties_provenance_node_readback_library_commit(idx_0, idx_1, idx_2);
                        root["ids_properties"]["provenance"]["node"][idx_0]["readback"][idx_1]["library"][idx_2]["description"] = get_ids_properties_provenance_node_readback_library_description(idx_0, idx_1, idx_2);
                        root["ids_properties"]["provenance"]["node"][idx_0]["readback"][idx_1]["library"][idx_2]["name"] = get_ids_properties_provenance_node_readback_library_name(idx_0, idx_1, idx_2);
                        root["ids_properties"]["provenance"]["node"][idx_0]["readback"][idx_1]["library"][idx_2]["parameters"] = get_ids_properties_provenance_node_readback_library_parameters(idx_0, idx_1, idx_2);
                        root["ids_properties"]["provenance"]["node"][idx_0]["readback"][idx_1]["library"][idx_2]["repository"] = get_ids_properties_provenance_node_readback_library_repository(idx_0, idx_1, idx_2);
                        root["ids_properties"]["provenance"]["node"][idx_0]["readback"][idx_1]["library"][idx_2]["version"] = get_ids_properties_provenance_node_readback_library_version(idx_0, idx_1, idx_2);
                    }
                    root["ids_properties"]["provenance"]["node"][idx_0]["readback"][idx_1]["name"] = get_ids_properties_provenance_node_readback_name(idx_0, idx_1);
                    root["ids_properties"]["provenance"]["node"][idx_0]["readback"][idx_1]["parameters"] = get_ids_properties_provenance_node_readback_parameters(idx_0, idx_1);
                    root["ids_properties"]["provenance"]["node"][idx_0]["readback"][idx_1]["repository"] = get_ids_properties_provenance_node_readback_repository(idx_0, idx_1);
                    root["ids_properties"]["provenance"]["node"][idx_0]["readback"][idx_1]["version"] = get_ids_properties_provenance_node_readback_version(idx_0, idx_1);
                }
                size_t size_ids_properties_provenance_node_reference = get_ids_properties_provenance_node_reference(idx_0);
                for (size_t idx_1 = 0; idx_1 < size_ids_properties_provenance_node_reference; ++idx_1) {
                    root["ids_properties"]["provenance"]["node"][idx_0]["reference"][idx_1]["name"] = get_ids_properties_provenance_node_reference_name(idx_0, idx_1);
                    root["ids_properties"]["provenance"]["node"][idx_0]["reference"][idx_1]["timestamp"] = get_ids_properties_provenance_node_reference_timestamp(idx_0, idx_1);
                }
            }
            root["ids_properties"]["provider"] = get_ids_properties_provider();
            root["ids_properties"]["version_put"]["access_layer"] = get_ids_properties_version_put_access_layer();
            root["ids_properties"]["version_put"]["access_layer_language"] = get_ids_properties_version_put_access_layer_language();
            root["ids_properties"]["version_put"]["data_dictionary"] = get_ids_properties_version_put_data_dictionary();
            size_t size_ip = get_ip();
            for (size_t idx_0 = 0; idx_0 < size_ip; ++idx_0) {
                root["ip"][idx_0]["data"] = get_ip_data(idx_0);
                root["ip"][idx_0]["data_error_lower"] = get_ip_data_error_lower(idx_0);
                root["ip"][idx_0]["data_error_upper"] = get_ip_data_error_upper(idx_0);
                root["ip"][idx_0]["method_name"] = get_ip_method_name(idx_0);
                root["ip"][idx_0]["time"] = get_ip_time(idx_0);
            }
            root["latency"] = get_latency();
            root["latency_error_lower"] = get_latency_error_lower();
            root["latency_error_upper"] = get_latency_error_upper();
            size_t size_rogowski_coil = get_rogowski_coil();
            for (size_t idx_0 = 0; idx_0 < size_rogowski_coil; ++idx_0) {
                root["rogowski_coil"][idx_0]["area"] = get_rogowski_coil_area(idx_0);
                root["rogowski_coil"][idx_0]["area_error_lower"] = get_rogowski_coil_area_error_lower(idx_0);
                root["rogowski_coil"][idx_0]["area_error_upper"] = get_rogowski_coil_area_error_upper(idx_0);
                root["rogowski_coil"][idx_0]["current"]["data"] = get_rogowski_coil_current_data(idx_0);
                root["rogowski_coil"][idx_0]["current"]["data_error_lower"] = get_rogowski_coil_current_data_error_lower(idx_0);
                root["rogowski_coil"][idx_0]["current"]["data_error_upper"] = get_rogowski_coil_current_data_error_upper(idx_0);
                root["rogowski_coil"][idx_0]["current"]["time"] = get_rogowski_coil_current_time(idx_0);
                root["rogowski_coil"][idx_0]["current"]["validity"] = get_rogowski_coil_current_validity(idx_0);
                root["rogowski_coil"][idx_0]["current"]["validity_timed"] = get_rogowski_coil_current_validity_timed(idx_0);
                root["rogowski_coil"][idx_0]["description"] = get_rogowski_coil_description(idx_0);
                root["rogowski_coil"][idx_0]["indices_compound"] = get_rogowski_coil_indices_compound(idx_0);
                root["rogowski_coil"][idx_0]["measured_quantity"]["description"] = get_rogowski_coil_measured_quantity_description(idx_0);
                root["rogowski_coil"][idx_0]["measured_quantity"]["index"] = get_rogowski_coil_measured_quantity_index(idx_0);
                root["rogowski_coil"][idx_0]["measured_quantity"]["name"] = get_rogowski_coil_measured_quantity_name(idx_0);
                root["rogowski_coil"][idx_0]["name"] = get_rogowski_coil_name(idx_0);
                size_t size_rogowski_coil_position = get_rogowski_coil_position(idx_0);
                for (size_t idx_1 = 0; idx_1 < size_rogowski_coil_position; ++idx_1) {
                    root["rogowski_coil"][idx_0]["position"][idx_1]["first_point"]["r"] = get_rogowski_coil_position_first_point_r(idx_0, idx_1);
                    root["rogowski_coil"][idx_0]["position"][idx_1]["first_point"]["r_error_lower"] = get_rogowski_coil_position_first_point_r_error_lower(idx_0, idx_1);
                    root["rogowski_coil"][idx_0]["position"][idx_1]["first_point"]["r_error_upper"] = get_rogowski_coil_position_first_point_r_error_upper(idx_0, idx_1);
                    root["rogowski_coil"][idx_0]["position"][idx_1]["first_point"]["z"] = get_rogowski_coil_position_first_point_z(idx_0, idx_1);
                    root["rogowski_coil"][idx_0]["position"][idx_1]["first_point"]["z_error_lower"] = get_rogowski_coil_position_first_point_z_error_lower(idx_0, idx_1);
                    root["rogowski_coil"][idx_0]["position"][idx_1]["first_point"]["z_error_upper"] = get_rogowski_coil_position_first_point_z_error_upper(idx_0, idx_1);
                    root["rogowski_coil"][idx_0]["position"][idx_1]["phi"] = get_rogowski_coil_position_phi(idx_0, idx_1);
                    root["rogowski_coil"][idx_0]["position"][idx_1]["phi_error_lower"] = get_rogowski_coil_position_phi_error_lower(idx_0, idx_1);
                    root["rogowski_coil"][idx_0]["position"][idx_1]["phi_error_upper"] = get_rogowski_coil_position_phi_error_upper(idx_0, idx_1);
                    root["rogowski_coil"][idx_0]["position"][idx_1]["r"] = get_rogowski_coil_position_r(idx_0, idx_1);
                    root["rogowski_coil"][idx_0]["position"][idx_1]["r_error_lower"] = get_rogowski_coil_position_r_error_lower(idx_0, idx_1);
                    root["rogowski_coil"][idx_0]["position"][idx_1]["r_error_upper"] = get_rogowski_coil_position_r_error_upper(idx_0, idx_1);
                    root["rogowski_coil"][idx_0]["position"][idx_1]["second_point"]["r"] = get_rogowski_coil_position_second_point_r(idx_0, idx_1);
                    root["rogowski_coil"][idx_0]["position"][idx_1]["second_point"]["r_error_lower"] = get_rogowski_coil_position_second_point_r_error_lower(idx_0, idx_1);
                    root["rogowski_coil"][idx_0]["position"][idx_1]["second_point"]["r_error_upper"] = get_rogowski_coil_position_second_point_r_error_upper(idx_0, idx_1);
                    root["rogowski_coil"][idx_0]["position"][idx_1]["second_point"]["z"] = get_rogowski_coil_position_second_point_z(idx_0, idx_1);
                    root["rogowski_coil"][idx_0]["position"][idx_1]["second_point"]["z_error_lower"] = get_rogowski_coil_position_second_point_z_error_lower(idx_0, idx_1);
                    root["rogowski_coil"][idx_0]["position"][idx_1]["second_point"]["z_error_upper"] = get_rogowski_coil_position_second_point_z_error_upper(idx_0, idx_1);
                    root["rogowski_coil"][idx_0]["position"][idx_1]["z"] = get_rogowski_coil_position_z(idx_0, idx_1);
                    root["rogowski_coil"][idx_0]["position"][idx_1]["z_error_lower"] = get_rogowski_coil_position_z_error_lower(idx_0, idx_1);
                    root["rogowski_coil"][idx_0]["position"][idx_1]["z_error_upper"] = get_rogowski_coil_position_z_error_upper(idx_0, idx_1);
                }
                root["rogowski_coil"][idx_0]["turns_per_metre"] = get_rogowski_coil_turns_per_metre(idx_0);
                root["rogowski_coil"][idx_0]["turns_per_metre_error_lower"] = get_rogowski_coil_turns_per_metre_error_lower(idx_0);
                root["rogowski_coil"][idx_0]["turns_per_metre_error_upper"] = get_rogowski_coil_turns_per_metre_error_upper(idx_0);
            }
            size_t size_shunt = get_shunt();
            for (size_t idx_0 = 0; idx_0 < size_shunt; ++idx_0) {
                root["shunt"][idx_0]["description"] = get_shunt_description(idx_0);
                root["shunt"][idx_0]["divertor_index"] = get_shunt_divertor_index(idx_0);
                root["shunt"][idx_0]["name"] = get_shunt_name(idx_0);
                root["shunt"][idx_0]["position"]["first_point"]["r"] = get_shunt_position_first_point_r(idx_0);
                root["shunt"][idx_0]["position"]["first_point"]["r_error_lower"] = get_shunt_position_first_point_r_error_lower(idx_0);
                root["shunt"][idx_0]["position"]["first_point"]["r_error_upper"] = get_shunt_position_first_point_r_error_upper(idx_0);
                root["shunt"][idx_0]["position"]["first_point"]["z"] = get_shunt_position_first_point_z(idx_0);
                root["shunt"][idx_0]["position"]["first_point"]["z_error_lower"] = get_shunt_position_first_point_z_error_lower(idx_0);
                root["shunt"][idx_0]["position"]["first_point"]["z_error_upper"] = get_shunt_position_first_point_z_error_upper(idx_0);
                root["shunt"][idx_0]["position"]["phi"] = get_shunt_position_phi(idx_0);
                root["shunt"][idx_0]["position"]["phi_error_lower"] = get_shunt_position_phi_error_lower(idx_0);
                root["shunt"][idx_0]["position"]["phi_error_upper"] = get_shunt_position_phi_error_upper(idx_0);
                root["shunt"][idx_0]["position"]["r"] = get_shunt_position_r(idx_0);
                root["shunt"][idx_0]["position"]["r_error_lower"] = get_shunt_position_r_error_lower(idx_0);
                root["shunt"][idx_0]["position"]["r_error_upper"] = get_shunt_position_r_error_upper(idx_0);
                root["shunt"][idx_0]["position"]["second_point"]["r"] = get_shunt_position_second_point_r(idx_0);
                root["shunt"][idx_0]["position"]["second_point"]["r_error_lower"] = get_shunt_position_second_point_r_error_lower(idx_0);
                root["shunt"][idx_0]["position"]["second_point"]["r_error_upper"] = get_shunt_position_second_point_r_error_upper(idx_0);
                root["shunt"][idx_0]["position"]["second_point"]["z"] = get_shunt_position_second_point_z(idx_0);
                root["shunt"][idx_0]["position"]["second_point"]["z_error_lower"] = get_shunt_position_second_point_z_error_lower(idx_0);
                root["shunt"][idx_0]["position"]["second_point"]["z_error_upper"] = get_shunt_position_second_point_z_error_upper(idx_0);
                root["shunt"][idx_0]["position"]["z"] = get_shunt_position_z(idx_0);
                root["shunt"][idx_0]["position"]["z_error_lower"] = get_shunt_position_z_error_lower(idx_0);
                root["shunt"][idx_0]["position"]["z_error_upper"] = get_shunt_position_z_error_upper(idx_0);
                root["shunt"][idx_0]["resistance"] = get_shunt_resistance(idx_0);
                root["shunt"][idx_0]["resistance_error_lower"] = get_shunt_resistance_error_lower(idx_0);
                root["shunt"][idx_0]["resistance_error_upper"] = get_shunt_resistance_error_upper(idx_0);
                root["shunt"][idx_0]["target_index"] = get_shunt_target_index(idx_0);
                root["shunt"][idx_0]["tile_index"] = get_shunt_tile_index(idx_0);
                root["shunt"][idx_0]["voltage"]["data"] = get_shunt_voltage_data(idx_0);
                root["shunt"][idx_0]["voltage"]["data_error_lower"] = get_shunt_voltage_data_error_lower(idx_0);
                root["shunt"][idx_0]["voltage"]["data_error_upper"] = get_shunt_voltage_data_error_upper(idx_0);
                root["shunt"][idx_0]["voltage"]["time"] = get_shunt_voltage_time(idx_0);
                root["shunt"][idx_0]["voltage"]["validity"] = get_shunt_voltage_validity(idx_0);
                root["shunt"][idx_0]["voltage"]["validity_timed"] = get_shunt_voltage_validity_timed(idx_0);
            }
            root["time"] = get_time();

        return root;
    }

protected:
    // IDS Path: b_field_phi_probe
    virtual size_t get_b_field_phi_probe() {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: b_field_phi_probe[#]/area
    virtual double get_b_field_phi_probe_area(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/area_error_lower
    virtual double get_b_field_phi_probe_area_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/area_error_upper
    virtual double get_b_field_phi_probe_area_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/bandwidth_3db
    virtual std::vector<double> get_b_field_phi_probe_bandwidth_3db(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_phi_probe[#]/bandwidth_3db_error_lower
    virtual std::vector<double> get_b_field_phi_probe_bandwidth_3db_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_phi_probe[#]/bandwidth_3db_error_upper
    virtual std::vector<double> get_b_field_phi_probe_bandwidth_3db_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_phi_probe[#]/description
    virtual std::string get_b_field_phi_probe_description(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: b_field_phi_probe[#]/field/data
    virtual std::vector<double> get_b_field_phi_probe_field_data(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_phi_probe[#]/field/data_error_lower
    virtual std::vector<double> get_b_field_phi_probe_field_data_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_phi_probe[#]/field/data_error_upper
    virtual std::vector<double> get_b_field_phi_probe_field_data_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_phi_probe[#]/field/time
    virtual std::vector<double> get_b_field_phi_probe_field_time(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_phi_probe[#]/field/validity
    virtual int get_b_field_phi_probe_field_validity(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0;
    }

    // IDS Path: b_field_phi_probe[#]/field/validity_timed
    virtual std::vector<int> get_b_field_phi_probe_field_validity_timed(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_phi_probe[#]/indices_differential
    virtual std::vector<int> get_b_field_phi_probe_indices_differential(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_phi_probe[#]/length
    virtual double get_b_field_phi_probe_length(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/length_error_lower
    virtual double get_b_field_phi_probe_length_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/length_error_upper
    virtual double get_b_field_phi_probe_length_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/name
    virtual std::string get_b_field_phi_probe_name(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: b_field_phi_probe[#]/non_linear_response/b_field_linear
    virtual std::vector<double> get_b_field_phi_probe_non_linear_response_b_field_linear(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_phi_probe[#]/non_linear_response/b_field_linear_error_lower
    virtual std::vector<double> get_b_field_phi_probe_non_linear_response_b_field_linear_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_phi_probe[#]/non_linear_response/b_field_linear_error_upper
    virtual std::vector<double> get_b_field_phi_probe_non_linear_response_b_field_linear_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_phi_probe[#]/non_linear_response/b_field_non_linear
    virtual std::vector<double> get_b_field_phi_probe_non_linear_response_b_field_non_linear(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_phi_probe[#]/non_linear_response/b_field_non_linear_error_lower
    virtual std::vector<double> get_b_field_phi_probe_non_linear_response_b_field_non_linear_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_phi_probe[#]/non_linear_response/b_field_non_linear_error_upper
    virtual std::vector<double> get_b_field_phi_probe_non_linear_response_b_field_non_linear_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_phi_probe[#]/poloidal_angle
    virtual double get_b_field_phi_probe_poloidal_angle(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/poloidal_angle_error_lower
    virtual double get_b_field_phi_probe_poloidal_angle_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/poloidal_angle_error_upper
    virtual double get_b_field_phi_probe_poloidal_angle_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/position/first_point/r
    virtual double get_b_field_phi_probe_position_first_point_r(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/position/first_point/r_error_lower
    virtual double get_b_field_phi_probe_position_first_point_r_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/position/first_point/r_error_upper
    virtual double get_b_field_phi_probe_position_first_point_r_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/position/first_point/z
    virtual double get_b_field_phi_probe_position_first_point_z(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/position/first_point/z_error_lower
    virtual double get_b_field_phi_probe_position_first_point_z_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/position/first_point/z_error_upper
    virtual double get_b_field_phi_probe_position_first_point_z_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/position/phi
    virtual double get_b_field_phi_probe_position_phi(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/position/phi_error_lower
    virtual double get_b_field_phi_probe_position_phi_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/position/phi_error_upper
    virtual double get_b_field_phi_probe_position_phi_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/position/r
    virtual double get_b_field_phi_probe_position_r(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/position/r_error_lower
    virtual double get_b_field_phi_probe_position_r_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/position/r_error_upper
    virtual double get_b_field_phi_probe_position_r_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/position/second_point/r
    virtual double get_b_field_phi_probe_position_second_point_r(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/position/second_point/r_error_lower
    virtual double get_b_field_phi_probe_position_second_point_r_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/position/second_point/r_error_upper
    virtual double get_b_field_phi_probe_position_second_point_r_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/position/second_point/z
    virtual double get_b_field_phi_probe_position_second_point_z(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/position/second_point/z_error_lower
    virtual double get_b_field_phi_probe_position_second_point_z_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/position/second_point/z_error_upper
    virtual double get_b_field_phi_probe_position_second_point_z_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/position/z
    virtual double get_b_field_phi_probe_position_z(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/position/z_error_lower
    virtual double get_b_field_phi_probe_position_z_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/position/z_error_upper
    virtual double get_b_field_phi_probe_position_z_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/toroidal_angle
    virtual double get_b_field_phi_probe_toroidal_angle(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/toroidal_angle_error_lower
    virtual double get_b_field_phi_probe_toroidal_angle_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/toroidal_angle_error_upper
    virtual double get_b_field_phi_probe_toroidal_angle_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_phi_probe[#]/turns
    virtual int get_b_field_phi_probe_turns(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0;
    }

    // IDS Path: b_field_phi_probe[#]/type/description
    virtual std::string get_b_field_phi_probe_type_description(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: b_field_phi_probe[#]/type/index
    virtual int get_b_field_phi_probe_type_index(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0;
    }

    // IDS Path: b_field_phi_probe[#]/type/name
    virtual std::string get_b_field_phi_probe_type_name(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: b_field_phi_probe[#]/voltage/data
    virtual std::vector<double> get_b_field_phi_probe_voltage_data(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_phi_probe[#]/voltage/data_error_lower
    virtual std::vector<double> get_b_field_phi_probe_voltage_data_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_phi_probe[#]/voltage/data_error_upper
    virtual std::vector<double> get_b_field_phi_probe_voltage_data_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_phi_probe[#]/voltage/time
    virtual std::vector<double> get_b_field_phi_probe_voltage_time(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_phi_probe[#]/voltage/validity
    virtual int get_b_field_phi_probe_voltage_validity(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0;
    }

    // IDS Path: b_field_phi_probe[#]/voltage/validity_timed
    virtual std::vector<int> get_b_field_phi_probe_voltage_validity_timed(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_pol_probe
    virtual size_t get_b_field_pol_probe() {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: b_field_pol_probe[#]/area
    virtual double get_b_field_pol_probe_area(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/area_error_lower
    virtual double get_b_field_pol_probe_area_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/area_error_upper
    virtual double get_b_field_pol_probe_area_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/bandwidth_3db
    virtual std::vector<double> get_b_field_pol_probe_bandwidth_3db(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_pol_probe[#]/bandwidth_3db_error_lower
    virtual std::vector<double> get_b_field_pol_probe_bandwidth_3db_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_pol_probe[#]/bandwidth_3db_error_upper
    virtual std::vector<double> get_b_field_pol_probe_bandwidth_3db_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_pol_probe[#]/description
    virtual std::string get_b_field_pol_probe_description(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: b_field_pol_probe[#]/field/data
    virtual std::vector<double> get_b_field_pol_probe_field_data(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_pol_probe[#]/field/data_error_lower
    virtual std::vector<double> get_b_field_pol_probe_field_data_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_pol_probe[#]/field/data_error_upper
    virtual std::vector<double> get_b_field_pol_probe_field_data_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_pol_probe[#]/field/time
    virtual std::vector<double> get_b_field_pol_probe_field_time(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_pol_probe[#]/field/validity
    virtual int get_b_field_pol_probe_field_validity(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0;
    }

    // IDS Path: b_field_pol_probe[#]/field/validity_timed
    virtual std::vector<int> get_b_field_pol_probe_field_validity_timed(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_pol_probe[#]/indices_differential
    virtual std::vector<int> get_b_field_pol_probe_indices_differential(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_pol_probe[#]/length
    virtual double get_b_field_pol_probe_length(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/length_error_lower
    virtual double get_b_field_pol_probe_length_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/length_error_upper
    virtual double get_b_field_pol_probe_length_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/name
    virtual std::string get_b_field_pol_probe_name(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: b_field_pol_probe[#]/non_linear_response/b_field_linear
    virtual std::vector<double> get_b_field_pol_probe_non_linear_response_b_field_linear(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_pol_probe[#]/non_linear_response/b_field_linear_error_lower
    virtual std::vector<double> get_b_field_pol_probe_non_linear_response_b_field_linear_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_pol_probe[#]/non_linear_response/b_field_linear_error_upper
    virtual std::vector<double> get_b_field_pol_probe_non_linear_response_b_field_linear_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_pol_probe[#]/non_linear_response/b_field_non_linear
    virtual std::vector<double> get_b_field_pol_probe_non_linear_response_b_field_non_linear(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_pol_probe[#]/non_linear_response/b_field_non_linear_error_lower
    virtual std::vector<double> get_b_field_pol_probe_non_linear_response_b_field_non_linear_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_pol_probe[#]/non_linear_response/b_field_non_linear_error_upper
    virtual std::vector<double> get_b_field_pol_probe_non_linear_response_b_field_non_linear_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_pol_probe[#]/poloidal_angle
    virtual double get_b_field_pol_probe_poloidal_angle(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/poloidal_angle_error_lower
    virtual double get_b_field_pol_probe_poloidal_angle_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/poloidal_angle_error_upper
    virtual double get_b_field_pol_probe_poloidal_angle_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/position/first_point/r
    virtual double get_b_field_pol_probe_position_first_point_r(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/position/first_point/r_error_lower
    virtual double get_b_field_pol_probe_position_first_point_r_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/position/first_point/r_error_upper
    virtual double get_b_field_pol_probe_position_first_point_r_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/position/first_point/z
    virtual double get_b_field_pol_probe_position_first_point_z(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/position/first_point/z_error_lower
    virtual double get_b_field_pol_probe_position_first_point_z_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/position/first_point/z_error_upper
    virtual double get_b_field_pol_probe_position_first_point_z_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/position/phi
    virtual double get_b_field_pol_probe_position_phi(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/position/phi_error_lower
    virtual double get_b_field_pol_probe_position_phi_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/position/phi_error_upper
    virtual double get_b_field_pol_probe_position_phi_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/position/r
    virtual double get_b_field_pol_probe_position_r(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/position/r_error_lower
    virtual double get_b_field_pol_probe_position_r_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/position/r_error_upper
    virtual double get_b_field_pol_probe_position_r_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/position/second_point/r
    virtual double get_b_field_pol_probe_position_second_point_r(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/position/second_point/r_error_lower
    virtual double get_b_field_pol_probe_position_second_point_r_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/position/second_point/r_error_upper
    virtual double get_b_field_pol_probe_position_second_point_r_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/position/second_point/z
    virtual double get_b_field_pol_probe_position_second_point_z(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/position/second_point/z_error_lower
    virtual double get_b_field_pol_probe_position_second_point_z_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/position/second_point/z_error_upper
    virtual double get_b_field_pol_probe_position_second_point_z_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/position/z
    virtual double get_b_field_pol_probe_position_z(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/position/z_error_lower
    virtual double get_b_field_pol_probe_position_z_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/position/z_error_upper
    virtual double get_b_field_pol_probe_position_z_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/toroidal_angle
    virtual double get_b_field_pol_probe_toroidal_angle(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/toroidal_angle_error_lower
    virtual double get_b_field_pol_probe_toroidal_angle_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/toroidal_angle_error_upper
    virtual double get_b_field_pol_probe_toroidal_angle_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: b_field_pol_probe[#]/turns
    virtual int get_b_field_pol_probe_turns(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0;
    }

    // IDS Path: b_field_pol_probe[#]/type/description
    virtual std::string get_b_field_pol_probe_type_description(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: b_field_pol_probe[#]/type/index
    virtual int get_b_field_pol_probe_type_index(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0;
    }

    // IDS Path: b_field_pol_probe[#]/type/name
    virtual std::string get_b_field_pol_probe_type_name(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: b_field_pol_probe[#]/voltage/data
    virtual std::vector<double> get_b_field_pol_probe_voltage_data(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_pol_probe[#]/voltage/data_error_lower
    virtual std::vector<double> get_b_field_pol_probe_voltage_data_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_pol_probe[#]/voltage/data_error_upper
    virtual std::vector<double> get_b_field_pol_probe_voltage_data_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_pol_probe[#]/voltage/time
    virtual std::vector<double> get_b_field_pol_probe_voltage_time(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_pol_probe[#]/voltage/validity
    virtual int get_b_field_pol_probe_voltage_validity(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0;
    }

    // IDS Path: b_field_pol_probe[#]/voltage/validity_timed
    virtual std::vector<int> get_b_field_pol_probe_voltage_validity_timed(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: b_field_pol_probe_equivalent
    virtual NDData<int> get_b_field_pol_probe_equivalent() {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: code/commit
    virtual std::string get_code_commit() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: code/description
    virtual std::string get_code_description() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: code/library
    virtual size_t get_code_library() {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: code/library[#]/commit
    virtual std::string get_code_library_commit(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: code/library[#]/description
    virtual std::string get_code_library_description(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: code/library[#]/name
    virtual std::string get_code_library_name(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: code/library[#]/parameters
    virtual std::string get_code_library_parameters(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: code/library[#]/repository
    virtual std::string get_code_library_repository(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: code/library[#]/version
    virtual std::string get_code_library_version(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: code/name
    virtual std::string get_code_name() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: code/output_flag
    virtual std::vector<int> get_code_output_flag() {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: code/parameters
    virtual std::string get_code_parameters() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: code/repository
    virtual std::string get_code_repository() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: code/version
    virtual std::string get_code_version() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: diamagnetic_flux
    virtual size_t get_diamagnetic_flux() {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: diamagnetic_flux[#]/data
    virtual std::vector<double> get_diamagnetic_flux_data(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: diamagnetic_flux[#]/data_error_lower
    virtual std::vector<double> get_diamagnetic_flux_data_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: diamagnetic_flux[#]/data_error_upper
    virtual std::vector<double> get_diamagnetic_flux_data_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: diamagnetic_flux[#]/method_name
    virtual std::string get_diamagnetic_flux_method_name(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: diamagnetic_flux[#]/time
    virtual std::vector<double> get_diamagnetic_flux_time(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: flux_loop
    virtual size_t get_flux_loop() {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: flux_loop[#]/area
    virtual double get_flux_loop_area(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/area_error_lower
    virtual double get_flux_loop_area_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/area_error_upper
    virtual double get_flux_loop_area_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/description
    virtual std::string get_flux_loop_description(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: flux_loop[#]/flux/data
    virtual std::vector<double> get_flux_loop_flux_data(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: flux_loop[#]/flux/data_error_lower
    virtual std::vector<double> get_flux_loop_flux_data_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: flux_loop[#]/flux/data_error_upper
    virtual std::vector<double> get_flux_loop_flux_data_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: flux_loop[#]/flux/time
    virtual std::vector<double> get_flux_loop_flux_time(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: flux_loop[#]/flux/validity
    virtual int get_flux_loop_flux_validity(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0;
    }

    // IDS Path: flux_loop[#]/flux/validity_timed
    virtual std::vector<int> get_flux_loop_flux_validity_timed(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: flux_loop[#]/gm9
    virtual double get_flux_loop_gm9(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/gm9_error_lower
    virtual double get_flux_loop_gm9_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/gm9_error_upper
    virtual double get_flux_loop_gm9_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/indices_differential
    virtual std::vector<int> get_flux_loop_indices_differential(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: flux_loop[#]/name
    virtual std::string get_flux_loop_name(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: flux_loop[#]/position
    virtual size_t get_flux_loop_position(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: flux_loop[#]/position[#]/first_point/r
    virtual double get_flux_loop_position_first_point_r(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/position[#]/first_point/r_error_lower
    virtual double get_flux_loop_position_first_point_r_error_lower(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/position[#]/first_point/r_error_upper
    virtual double get_flux_loop_position_first_point_r_error_upper(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/position[#]/first_point/z
    virtual double get_flux_loop_position_first_point_z(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/position[#]/first_point/z_error_lower
    virtual double get_flux_loop_position_first_point_z_error_lower(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/position[#]/first_point/z_error_upper
    virtual double get_flux_loop_position_first_point_z_error_upper(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/position[#]/phi
    virtual double get_flux_loop_position_phi(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/position[#]/phi_error_lower
    virtual double get_flux_loop_position_phi_error_lower(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/position[#]/phi_error_upper
    virtual double get_flux_loop_position_phi_error_upper(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/position[#]/r
    virtual double get_flux_loop_position_r(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/position[#]/r_error_lower
    virtual double get_flux_loop_position_r_error_lower(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/position[#]/r_error_upper
    virtual double get_flux_loop_position_r_error_upper(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/position[#]/second_point/r
    virtual double get_flux_loop_position_second_point_r(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/position[#]/second_point/r_error_lower
    virtual double get_flux_loop_position_second_point_r_error_lower(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/position[#]/second_point/r_error_upper
    virtual double get_flux_loop_position_second_point_r_error_upper(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/position[#]/second_point/z
    virtual double get_flux_loop_position_second_point_z(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/position[#]/second_point/z_error_lower
    virtual double get_flux_loop_position_second_point_z_error_lower(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/position[#]/second_point/z_error_upper
    virtual double get_flux_loop_position_second_point_z_error_upper(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/position[#]/z
    virtual double get_flux_loop_position_z(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/position[#]/z_error_lower
    virtual double get_flux_loop_position_z_error_lower(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/position[#]/z_error_upper
    virtual double get_flux_loop_position_z_error_upper(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: flux_loop[#]/type/description
    virtual std::string get_flux_loop_type_description(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: flux_loop[#]/type/index
    virtual int get_flux_loop_type_index(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0;
    }

    // IDS Path: flux_loop[#]/type/name
    virtual std::string get_flux_loop_type_name(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: flux_loop[#]/voltage/data
    virtual std::vector<double> get_flux_loop_voltage_data(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: flux_loop[#]/voltage/data_error_lower
    virtual std::vector<double> get_flux_loop_voltage_data_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: flux_loop[#]/voltage/data_error_upper
    virtual std::vector<double> get_flux_loop_voltage_data_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: flux_loop[#]/voltage/time
    virtual std::vector<double> get_flux_loop_voltage_time(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: flux_loop[#]/voltage/validity
    virtual int get_flux_loop_voltage_validity(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0;
    }

    // IDS Path: flux_loop[#]/voltage/validity_timed
    virtual std::vector<int> get_flux_loop_voltage_validity_timed(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: ids_properties/comment
    virtual std::string get_ids_properties_comment() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/creation_date
    virtual std::string get_ids_properties_creation_date() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/homogeneous_time
    virtual int get_ids_properties_homogeneous_time() {
        // TODO: User implementation to fetch real data.
        return 0;
    }

    // IDS Path: ids_properties/name
    virtual std::string get_ids_properties_name() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/occurrence_type/description
    virtual std::string get_ids_properties_occurrence_type_description() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/occurrence_type/index
    virtual int get_ids_properties_occurrence_type_index() {
        // TODO: User implementation to fetch real data.
        return 0;
    }

    // IDS Path: ids_properties/occurrence_type/name
    virtual std::string get_ids_properties_occurrence_type_name() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/infrastructure_get/commit
    virtual std::string get_ids_properties_plugins_infrastructure_get_commit() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/infrastructure_get/description
    virtual std::string get_ids_properties_plugins_infrastructure_get_description() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/infrastructure_get/name
    virtual std::string get_ids_properties_plugins_infrastructure_get_name() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/infrastructure_get/repository
    virtual std::string get_ids_properties_plugins_infrastructure_get_repository() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/infrastructure_get/version
    virtual std::string get_ids_properties_plugins_infrastructure_get_version() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/infrastructure_put/commit
    virtual std::string get_ids_properties_plugins_infrastructure_put_commit() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/infrastructure_put/description
    virtual std::string get_ids_properties_plugins_infrastructure_put_description() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/infrastructure_put/name
    virtual std::string get_ids_properties_plugins_infrastructure_put_name() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/infrastructure_put/repository
    virtual std::string get_ids_properties_plugins_infrastructure_put_repository() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/infrastructure_put/version
    virtual std::string get_ids_properties_plugins_infrastructure_put_version() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node
    virtual size_t get_ids_properties_plugins_node() {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: ids_properties/plugins/node[#]/get_operation
    virtual size_t get_ids_properties_plugins_node_get_operation(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: ids_properties/plugins/node[#]/get_operation[#]/commit
    virtual std::string get_ids_properties_plugins_node_get_operation_commit(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/get_operation[#]/description
    virtual std::string get_ids_properties_plugins_node_get_operation_description(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/get_operation[#]/library
    virtual size_t get_ids_properties_plugins_node_get_operation_library(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: ids_properties/plugins/node[#]/get_operation[#]/library[#]/commit
    virtual std::string get_ids_properties_plugins_node_get_operation_library_commit(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/get_operation[#]/library[#]/description
    virtual std::string get_ids_properties_plugins_node_get_operation_library_description(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/get_operation[#]/library[#]/name
    virtual std::string get_ids_properties_plugins_node_get_operation_library_name(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/get_operation[#]/library[#]/parameters
    virtual std::string get_ids_properties_plugins_node_get_operation_library_parameters(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/get_operation[#]/library[#]/repository
    virtual std::string get_ids_properties_plugins_node_get_operation_library_repository(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/get_operation[#]/library[#]/version
    virtual std::string get_ids_properties_plugins_node_get_operation_library_version(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/get_operation[#]/name
    virtual std::string get_ids_properties_plugins_node_get_operation_name(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/get_operation[#]/parameters
    virtual std::string get_ids_properties_plugins_node_get_operation_parameters(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/get_operation[#]/repository
    virtual std::string get_ids_properties_plugins_node_get_operation_repository(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/get_operation[#]/version
    virtual std::string get_ids_properties_plugins_node_get_operation_version(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/path
    virtual std::string get_ids_properties_plugins_node_path(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/put_operation
    virtual size_t get_ids_properties_plugins_node_put_operation(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: ids_properties/plugins/node[#]/put_operation[#]/commit
    virtual std::string get_ids_properties_plugins_node_put_operation_commit(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/put_operation[#]/description
    virtual std::string get_ids_properties_plugins_node_put_operation_description(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/put_operation[#]/library
    virtual size_t get_ids_properties_plugins_node_put_operation_library(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: ids_properties/plugins/node[#]/put_operation[#]/library[#]/commit
    virtual std::string get_ids_properties_plugins_node_put_operation_library_commit(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/put_operation[#]/library[#]/description
    virtual std::string get_ids_properties_plugins_node_put_operation_library_description(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/put_operation[#]/library[#]/name
    virtual std::string get_ids_properties_plugins_node_put_operation_library_name(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/put_operation[#]/library[#]/parameters
    virtual std::string get_ids_properties_plugins_node_put_operation_library_parameters(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/put_operation[#]/library[#]/repository
    virtual std::string get_ids_properties_plugins_node_put_operation_library_repository(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/put_operation[#]/library[#]/version
    virtual std::string get_ids_properties_plugins_node_put_operation_library_version(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/put_operation[#]/name
    virtual std::string get_ids_properties_plugins_node_put_operation_name(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/put_operation[#]/parameters
    virtual std::string get_ids_properties_plugins_node_put_operation_parameters(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/put_operation[#]/repository
    virtual std::string get_ids_properties_plugins_node_put_operation_repository(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/put_operation[#]/version
    virtual std::string get_ids_properties_plugins_node_put_operation_version(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/readback
    virtual size_t get_ids_properties_plugins_node_readback(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: ids_properties/plugins/node[#]/readback[#]/commit
    virtual std::string get_ids_properties_plugins_node_readback_commit(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/readback[#]/description
    virtual std::string get_ids_properties_plugins_node_readback_description(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/readback[#]/library
    virtual size_t get_ids_properties_plugins_node_readback_library(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: ids_properties/plugins/node[#]/readback[#]/library[#]/commit
    virtual std::string get_ids_properties_plugins_node_readback_library_commit(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/readback[#]/library[#]/description
    virtual std::string get_ids_properties_plugins_node_readback_library_description(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/readback[#]/library[#]/name
    virtual std::string get_ids_properties_plugins_node_readback_library_name(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/readback[#]/library[#]/parameters
    virtual std::string get_ids_properties_plugins_node_readback_library_parameters(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/readback[#]/library[#]/repository
    virtual std::string get_ids_properties_plugins_node_readback_library_repository(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/readback[#]/library[#]/version
    virtual std::string get_ids_properties_plugins_node_readback_library_version(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/readback[#]/name
    virtual std::string get_ids_properties_plugins_node_readback_name(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/readback[#]/parameters
    virtual std::string get_ids_properties_plugins_node_readback_parameters(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/readback[#]/repository
    virtual std::string get_ids_properties_plugins_node_readback_repository(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/readback[#]/version
    virtual std::string get_ids_properties_plugins_node_readback_version(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/reference
    virtual size_t get_ids_properties_plugins_node_reference(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: ids_properties/plugins/node[#]/reference[#]/name
    virtual std::string get_ids_properties_plugins_node_reference_name(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/plugins/node[#]/reference[#]/timestamp
    virtual std::string get_ids_properties_plugins_node_reference_timestamp(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node
    virtual size_t get_ids_properties_provenance_node() {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: ids_properties/provenance/node[#]/get_operation
    virtual size_t get_ids_properties_provenance_node_get_operation(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: ids_properties/provenance/node[#]/get_operation[#]/commit
    virtual std::string get_ids_properties_provenance_node_get_operation_commit(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/get_operation[#]/description
    virtual std::string get_ids_properties_provenance_node_get_operation_description(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/get_operation[#]/library
    virtual size_t get_ids_properties_provenance_node_get_operation_library(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: ids_properties/provenance/node[#]/get_operation[#]/library[#]/commit
    virtual std::string get_ids_properties_provenance_node_get_operation_library_commit(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/get_operation[#]/library[#]/description
    virtual std::string get_ids_properties_provenance_node_get_operation_library_description(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/get_operation[#]/library[#]/name
    virtual std::string get_ids_properties_provenance_node_get_operation_library_name(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/get_operation[#]/library[#]/parameters
    virtual std::string get_ids_properties_provenance_node_get_operation_library_parameters(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/get_operation[#]/library[#]/repository
    virtual std::string get_ids_properties_provenance_node_get_operation_library_repository(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/get_operation[#]/library[#]/version
    virtual std::string get_ids_properties_provenance_node_get_operation_library_version(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/get_operation[#]/name
    virtual std::string get_ids_properties_provenance_node_get_operation_name(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/get_operation[#]/parameters
    virtual std::string get_ids_properties_provenance_node_get_operation_parameters(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/get_operation[#]/repository
    virtual std::string get_ids_properties_provenance_node_get_operation_repository(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/get_operation[#]/version
    virtual std::string get_ids_properties_provenance_node_get_operation_version(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/path
    virtual std::string get_ids_properties_provenance_node_path(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/put_operation
    virtual size_t get_ids_properties_provenance_node_put_operation(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: ids_properties/provenance/node[#]/put_operation[#]/commit
    virtual std::string get_ids_properties_provenance_node_put_operation_commit(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/put_operation[#]/description
    virtual std::string get_ids_properties_provenance_node_put_operation_description(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/put_operation[#]/library
    virtual size_t get_ids_properties_provenance_node_put_operation_library(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: ids_properties/provenance/node[#]/put_operation[#]/library[#]/commit
    virtual std::string get_ids_properties_provenance_node_put_operation_library_commit(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/put_operation[#]/library[#]/description
    virtual std::string get_ids_properties_provenance_node_put_operation_library_description(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/put_operation[#]/library[#]/name
    virtual std::string get_ids_properties_provenance_node_put_operation_library_name(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/put_operation[#]/library[#]/parameters
    virtual std::string get_ids_properties_provenance_node_put_operation_library_parameters(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/put_operation[#]/library[#]/repository
    virtual std::string get_ids_properties_provenance_node_put_operation_library_repository(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/put_operation[#]/library[#]/version
    virtual std::string get_ids_properties_provenance_node_put_operation_library_version(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/put_operation[#]/name
    virtual std::string get_ids_properties_provenance_node_put_operation_name(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/put_operation[#]/parameters
    virtual std::string get_ids_properties_provenance_node_put_operation_parameters(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/put_operation[#]/repository
    virtual std::string get_ids_properties_provenance_node_put_operation_repository(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/put_operation[#]/version
    virtual std::string get_ids_properties_provenance_node_put_operation_version(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/readback
    virtual size_t get_ids_properties_provenance_node_readback(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: ids_properties/provenance/node[#]/readback[#]/commit
    virtual std::string get_ids_properties_provenance_node_readback_commit(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/readback[#]/description
    virtual std::string get_ids_properties_provenance_node_readback_description(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/readback[#]/library
    virtual size_t get_ids_properties_provenance_node_readback_library(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: ids_properties/provenance/node[#]/readback[#]/library[#]/commit
    virtual std::string get_ids_properties_provenance_node_readback_library_commit(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/readback[#]/library[#]/description
    virtual std::string get_ids_properties_provenance_node_readback_library_description(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/readback[#]/library[#]/name
    virtual std::string get_ids_properties_provenance_node_readback_library_name(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/readback[#]/library[#]/parameters
    virtual std::string get_ids_properties_provenance_node_readback_library_parameters(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/readback[#]/library[#]/repository
    virtual std::string get_ids_properties_provenance_node_readback_library_repository(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/readback[#]/library[#]/version
    virtual std::string get_ids_properties_provenance_node_readback_library_version(size_t idx_0, size_t idx_1, size_t idx_2) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/readback[#]/name
    virtual std::string get_ids_properties_provenance_node_readback_name(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/readback[#]/parameters
    virtual std::string get_ids_properties_provenance_node_readback_parameters(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/readback[#]/repository
    virtual std::string get_ids_properties_provenance_node_readback_repository(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/readback[#]/version
    virtual std::string get_ids_properties_provenance_node_readback_version(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/reference
    virtual size_t get_ids_properties_provenance_node_reference(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: ids_properties/provenance/node[#]/reference[#]/name
    virtual std::string get_ids_properties_provenance_node_reference_name(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provenance/node[#]/reference[#]/timestamp
    virtual std::string get_ids_properties_provenance_node_reference_timestamp(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/provider
    virtual std::string get_ids_properties_provider() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/version_put/access_layer
    virtual std::string get_ids_properties_version_put_access_layer() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/version_put/access_layer_language
    virtual std::string get_ids_properties_version_put_access_layer_language() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ids_properties/version_put/data_dictionary
    virtual std::string get_ids_properties_version_put_data_dictionary() {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ip
    virtual size_t get_ip() {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: ip[#]/data
    virtual std::vector<double> get_ip_data(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: ip[#]/data_error_lower
    virtual std::vector<double> get_ip_data_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: ip[#]/data_error_upper
    virtual std::vector<double> get_ip_data_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: ip[#]/method_name
    virtual std::string get_ip_method_name(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: ip[#]/time
    virtual std::vector<double> get_ip_time(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: latency
    virtual double get_latency() {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: latency_error_lower
    virtual double get_latency_error_lower() {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: latency_error_upper
    virtual double get_latency_error_upper() {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil
    virtual size_t get_rogowski_coil() {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: rogowski_coil[#]/area
    virtual double get_rogowski_coil_area(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/area_error_lower
    virtual double get_rogowski_coil_area_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/area_error_upper
    virtual double get_rogowski_coil_area_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/current/data
    virtual std::vector<double> get_rogowski_coil_current_data(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: rogowski_coil[#]/current/data_error_lower
    virtual std::vector<double> get_rogowski_coil_current_data_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: rogowski_coil[#]/current/data_error_upper
    virtual std::vector<double> get_rogowski_coil_current_data_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: rogowski_coil[#]/current/time
    virtual std::vector<double> get_rogowski_coil_current_time(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: rogowski_coil[#]/current/validity
    virtual int get_rogowski_coil_current_validity(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0;
    }

    // IDS Path: rogowski_coil[#]/current/validity_timed
    virtual std::vector<int> get_rogowski_coil_current_validity_timed(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: rogowski_coil[#]/description
    virtual std::string get_rogowski_coil_description(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: rogowski_coil[#]/indices_compound
    virtual std::vector<int> get_rogowski_coil_indices_compound(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: rogowski_coil[#]/measured_quantity/description
    virtual std::string get_rogowski_coil_measured_quantity_description(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: rogowski_coil[#]/measured_quantity/index
    virtual int get_rogowski_coil_measured_quantity_index(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0;
    }

    // IDS Path: rogowski_coil[#]/measured_quantity/name
    virtual std::string get_rogowski_coil_measured_quantity_name(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: rogowski_coil[#]/name
    virtual std::string get_rogowski_coil_name(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: rogowski_coil[#]/position
    virtual size_t get_rogowski_coil_position(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: rogowski_coil[#]/position[#]/first_point/r
    virtual double get_rogowski_coil_position_first_point_r(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/position[#]/first_point/r_error_lower
    virtual double get_rogowski_coil_position_first_point_r_error_lower(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/position[#]/first_point/r_error_upper
    virtual double get_rogowski_coil_position_first_point_r_error_upper(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/position[#]/first_point/z
    virtual double get_rogowski_coil_position_first_point_z(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/position[#]/first_point/z_error_lower
    virtual double get_rogowski_coil_position_first_point_z_error_lower(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/position[#]/first_point/z_error_upper
    virtual double get_rogowski_coil_position_first_point_z_error_upper(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/position[#]/phi
    virtual double get_rogowski_coil_position_phi(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/position[#]/phi_error_lower
    virtual double get_rogowski_coil_position_phi_error_lower(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/position[#]/phi_error_upper
    virtual double get_rogowski_coil_position_phi_error_upper(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/position[#]/r
    virtual double get_rogowski_coil_position_r(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/position[#]/r_error_lower
    virtual double get_rogowski_coil_position_r_error_lower(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/position[#]/r_error_upper
    virtual double get_rogowski_coil_position_r_error_upper(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/position[#]/second_point/r
    virtual double get_rogowski_coil_position_second_point_r(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/position[#]/second_point/r_error_lower
    virtual double get_rogowski_coil_position_second_point_r_error_lower(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/position[#]/second_point/r_error_upper
    virtual double get_rogowski_coil_position_second_point_r_error_upper(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/position[#]/second_point/z
    virtual double get_rogowski_coil_position_second_point_z(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/position[#]/second_point/z_error_lower
    virtual double get_rogowski_coil_position_second_point_z_error_lower(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/position[#]/second_point/z_error_upper
    virtual double get_rogowski_coil_position_second_point_z_error_upper(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/position[#]/z
    virtual double get_rogowski_coil_position_z(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/position[#]/z_error_lower
    virtual double get_rogowski_coil_position_z_error_lower(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/position[#]/z_error_upper
    virtual double get_rogowski_coil_position_z_error_upper(size_t idx_0, size_t idx_1) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/turns_per_metre
    virtual double get_rogowski_coil_turns_per_metre(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/turns_per_metre_error_lower
    virtual double get_rogowski_coil_turns_per_metre_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: rogowski_coil[#]/turns_per_metre_error_upper
    virtual double get_rogowski_coil_turns_per_metre_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt
    virtual size_t get_shunt() {
        // TODO: User implementation to fetch real data.
        return 2;
    }

    // IDS Path: shunt[#]/description
    virtual std::string get_shunt_description(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: shunt[#]/divertor_index
    virtual int get_shunt_divertor_index(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0;
    }

    // IDS Path: shunt[#]/name
    virtual std::string get_shunt_name(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return "";
    }

    // IDS Path: shunt[#]/position/first_point/r
    virtual double get_shunt_position_first_point_r(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt[#]/position/first_point/r_error_lower
    virtual double get_shunt_position_first_point_r_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt[#]/position/first_point/r_error_upper
    virtual double get_shunt_position_first_point_r_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt[#]/position/first_point/z
    virtual double get_shunt_position_first_point_z(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt[#]/position/first_point/z_error_lower
    virtual double get_shunt_position_first_point_z_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt[#]/position/first_point/z_error_upper
    virtual double get_shunt_position_first_point_z_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt[#]/position/phi
    virtual double get_shunt_position_phi(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt[#]/position/phi_error_lower
    virtual double get_shunt_position_phi_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt[#]/position/phi_error_upper
    virtual double get_shunt_position_phi_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt[#]/position/r
    virtual double get_shunt_position_r(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt[#]/position/r_error_lower
    virtual double get_shunt_position_r_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt[#]/position/r_error_upper
    virtual double get_shunt_position_r_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt[#]/position/second_point/r
    virtual double get_shunt_position_second_point_r(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt[#]/position/second_point/r_error_lower
    virtual double get_shunt_position_second_point_r_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt[#]/position/second_point/r_error_upper
    virtual double get_shunt_position_second_point_r_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt[#]/position/second_point/z
    virtual double get_shunt_position_second_point_z(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt[#]/position/second_point/z_error_lower
    virtual double get_shunt_position_second_point_z_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt[#]/position/second_point/z_error_upper
    virtual double get_shunt_position_second_point_z_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt[#]/position/z
    virtual double get_shunt_position_z(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt[#]/position/z_error_lower
    virtual double get_shunt_position_z_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt[#]/position/z_error_upper
    virtual double get_shunt_position_z_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt[#]/resistance
    virtual double get_shunt_resistance(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt[#]/resistance_error_lower
    virtual double get_shunt_resistance_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt[#]/resistance_error_upper
    virtual double get_shunt_resistance_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0.0;
    }

    // IDS Path: shunt[#]/target_index
    virtual int get_shunt_target_index(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0;
    }

    // IDS Path: shunt[#]/tile_index
    virtual int get_shunt_tile_index(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0;
    }

    // IDS Path: shunt[#]/voltage/data
    virtual std::vector<double> get_shunt_voltage_data(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: shunt[#]/voltage/data_error_lower
    virtual std::vector<double> get_shunt_voltage_data_error_lower(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: shunt[#]/voltage/data_error_upper
    virtual std::vector<double> get_shunt_voltage_data_error_upper(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: shunt[#]/voltage/time
    virtual std::vector<double> get_shunt_voltage_time(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: shunt[#]/voltage/validity
    virtual int get_shunt_voltage_validity(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return 0;
    }

    // IDS Path: shunt[#]/voltage/validity_timed
    virtual std::vector<int> get_shunt_voltage_validity_timed(size_t idx_0) {
        // TODO: User implementation to fetch real data.
        return {};
    }

    // IDS Path: time
    virtual std::vector<double> get_time() {
        // TODO: User implementation to fetch real data.
        return {};
    }

};
