#include <torch/torch.h>
#include <iostream>
#include <chrono>

using std::chrono::high_resolution_clock;

// Execution initial time
auto t1 { high_resolution_clock::now() };

// N is the batch size - Refers to how many data samples are processed at once. Using batches improves training efficiency.
// D_in is the input layer - Number of input features for each sample.
// H is the hiddden layer - Number of neurons in the intermediate layer, which captures patterns from the input.
// D_out is the output layer - Number of outputs per sample (e.g., 10 classes if it's a classification problem).
const int64_t N{ 64 };
const int64_t D_in{ 1000 };
const int64_t H{ 100 };
const int64_t D_out{ 10 };

// Class - Represents the neural network, inheriting from torch::nn::Module (base class for all PyTorch models).
class Lab : public torch::nn::Module {

	
	public:

		// Constructor
		Lab() : linear1(D_in, H), linear2(H, D_out) {

			// linear1 and linear2: connects the input layer to the hidden layer, taking D_in and producing H outputs.
			// register_module: tracks the layers for PyTorch to manage their parameters.
			register_module("Linear1", linear1); 
			register_module("Linear2", linear2);

		}

		// Forward - Defines how data flows through the model
		torch::Tensor forward(torch::Tensor x) {

			// Applies a linear transformation with linear1.
			// Applies ReLU (Rectified Linear Unit), an activation function that adds non-linearity: ReLU(𝑥)=max(0,𝑥) ReLU(x) = max(0, x).
			x = torch::relu(linear1->forward(x));

			// Passes the result through linear2 for the final output.
			x = linear2->forward(x);

			return x;
		}

		// Variables

		torch::nn::Linear linear1;
		torch::nn::Linear linear2;


};



int main()
{

	using std::chrono::high_resolution_clock;
	using std::chrono::duration_cast;
	using std::chrono::duration;
	using std::chrono::microseconds;

	// Seed
	torch::manual_seed(1);

	// Random values - Creating Input and Target Data
	torch::Tensor x = torch::rand({ N, D_in });  // Randomly generates 𝑁 × 𝐷_𝑖𝑛	data samples.
	torch::Tensor y = torch::rand({ N, D_out });  // Randomly generates 𝑁 ×	𝐷_𝑜𝑢𝑡 values to represent expected outputs.
	
	// Device Setup - Specifies the device (CPU) where computations will run. It can be set to torch::kCUDA to use a GPU.
	torch::Device device(torch::kCPU); // kCUDA

	// Defining the model
	Lab model;

	// Copying the model to the device
	model.to(device);

	// Learning - Controls how much the model adjusts weights in response to the error.
	float_t learning_rate = 1e-4;

	// Optimizer - Updates the model parameters (weights) using stochastic gradient descent
	torch::optim::SGD optimizer(model.parameters(), torch::optim::SGDOptions(learning_rate));

	// Train Loop
	for (size_t epoch = 1; epoch <= 500; ++epoch) {

		// Model prediction
		auto y_pred = model.forward(x);

		// Loss calulation
		auto loss = torch::mse_loss(y_pred, y.detach());

		// Print loss
		if (epoch % 100 == 99) {

			std::cout << "Epoch = " << epoch << " - Error = " << loss << "\n";

		}

		// Zero gradients -  Clears gradients from the previous step to avoid accumulation.
		optimizer.zero_grad(); 

		// Backpropagation - Computes gradients of the loss with respect to the weights
		loss.backward();

		// Weights update - Updates the weights based on the computed gradients and learning rate.
		optimizer.step();
	
	}

	// End time
	auto t2 = high_resolution_clock::now();

	// Calculate duration
	duration<double, std::milli> ms_double{ t2 - t1 };
	std::cout << "Runtime = " << ms_double.count() << " ms" << std::endl;

	return 0;

};
