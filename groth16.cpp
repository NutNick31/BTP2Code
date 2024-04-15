#include <iostream>
#include <libsnark/common/default_types/r1cs_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_ppzksnark/r1cs_ppzksnark.hpp>

using namespace libsnark;

// Define the types for the protoboard
typedef libsnark::default_r1cs_ppzksnark_pp default_ppzksnark_pp;
typedef default_ppzksnark_pp::scalar_field_type FieldT;

int main() {
    // Initialize the curve parameters
    default_ppzksnark_pp::init_public_params();

    // Define the constraint system
    protoboard<FieldT> pb;

    // Define variables
    pb_variable<FieldT> x, y, z;
    x.allocate(pb, "x");
    y.allocate(pb, "y");
    z.allocate(pb, "z");

    // Define the constraint: z = x * y
    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(x, y, z));

    // Generate the key pair
    r1cs_ppzksnark_keypair<default_ppzksnark_pp> keypair = r1cs_ppzksnark_generator<default_ppzksnark_pp>(pb);

    // Generate a proof
    r1cs_ppzksnark_proof<default_ppzksnark_pp> proof = r1cs_ppzksnark_prover<default_ppzksnark_pp>(keypair.pk, pb.primary_input(), pb.auxiliary_input());

    // Verify the proof
    bool verified = r1cs_ppzksnark_verifier_strong_IC<default_ppzksnark_pp>(keypair.vk, pb.primary_input(), proof);

    // Output the result
    std::cout << "Proof verified: " << (verified ? "true" : "false") << std::endl;

    return 0;
}
