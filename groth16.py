from snarky import Circuit

# Define the circuit
@circuit
def groth16_circuit(x, y):
    z = x * y
    return z

# Setup
params = Circuit.setup()

# Generate proving and verification keys
pk, vk = Circuit.generate_keys(groth16_circuit, params)

# Define inputs
x = 5
y = 7

# Generate a proof
proof = Circuit.prove(groth16_circuit, params, pk, [x, y])

# Verify the proof
assert Circuit.verify(groth16_circuit, params, vk, proof, [x, y])

print("Proof verified successfully!")
