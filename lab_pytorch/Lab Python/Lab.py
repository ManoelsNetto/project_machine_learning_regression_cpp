# import
import torch
import time

# Class
class Model(torch.nn.Module):
    
    # Constructor
    def __init__(self, D_in, H, D_out):
        super(Model, self).__init__()
        self.linear1 = torch.nn.Linear(D_in, H)
        self.linear2 = torch.nn.Linear(H, D_out)
    
    # Method
    def forward(self, x):
        h_relu = self.linear1(x).clamp(min=0)
        y_pred = self.linear2(h_relu)
        return y_pred
    
# N é o batch size
# D_in é a camada de entrada
# H é a camada oculta
# D_out é a camada de saída
N, D_in, H, D_out = 64, 1000, 100, 10

x = torch.randn(N, D_in)
y = torch.randn(N, D_out)

start_time = time.time()
model = Model(D_in, H, D_out)

# Error Function
loss_fn = torch.nn.MSELoss(reduction = 'sum')

# Learning rate
learning_rate = 1e-4

# Optimization SGD
optimizer = torch.optim.SGD(model.parameters(), lr = learning_rate)

for t in range(500):
    
    # Forward pass: y prediction
    y_pred = model(x)
    
    # Loss
    loss = loss_fn(y_pred, y)
    
    if (t % 100 == 99):
        print("Epoch = {}, Error = {}".format(t, loss.item()))
        
    # Zero gradiants
    optimizer.zero_grad()
    
    # Backpropagtion
    loss.backward()
    
    # Update weights
    optimizer.step()
    
print("\n--- Execution time: %s ---\n" % (time.time() - start_time))