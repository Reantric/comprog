import numpy as np

num_simulations = 1000
# Corrected transition matrix based on the user's input
P = np.array([
    [0,   2/3, 1/3, 0,   0,   0  ],
    [1/4, 1/2, 1/4, 0,   0,   0  ],
    [3/5, 2/5, 0,   0,   0,   0  ],
    [1/2, 0,   0,   0,   1/2, 0  ],
    [0,   1/3, 0,   1/3, 0,   1/3],
    [0,   0,   0,   1/2, 1/2, 0  ]
])

def simulate_return_to_A(P, max_steps=1000):
  counter = 0
  current_state = 3 # Start from state A, which is index 0
  for _ in range(max_steps):
      counter += 1
      next_state = np.random.choice(np.arange(P.shape[1]), p=P[current_state])
      if next_state == 3: # If we've returned to A, return True
          return counter
      current_state = next_state
  return counter # If we haven't returned to A within max_steps, return False


# Running the simulations with the corrected matrix
returns_to_A_corrected = sum(simulate_return_to_A(P) for _ in range(num_simulations))

# Estimating the probability with the corrected matrix
estimated_probability_corrected = returns_to_A_corrected / num_simulations
print(estimated_probability_corrected)
