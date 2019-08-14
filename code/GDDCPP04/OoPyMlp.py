import random
class Weight:
    
    alpha = 0.2
    def __init__(self):
        self.weight =0.0
        self.node_from = None
        self.node_to = None
    
    def getOutput(self):
        return self.weight * self.node_from.output
        
    def getDelta(self):
        return self.weight * self.node_to.delta
        
    def update(self):
        self.weight -= self.node_from.output * self.node_to.delta * Weight.alpha


class Node:
    
    def __init__(self,actfun=None,divfun=None):
        self.weights_in=[]
        self.weights_out=[]
        self.output = 0.0
        self.delta = 0.0
        self.actfun = actfun
        self.divfun = divfun
        
    def feedfoward(self):
        value = 0.0
        for w in self.weights_in:
            value+= w.getOutput()
        self.output = self.actfun(value)
        
    def calcDelta(self):
        error = 0.0
        for w in self.weights_out:
            error += w.getDelta()
        self.delta = self.divfun(output) * error
        
    def addWeightIn(self,w):
        self.weights_in.append(w)
        w.node_to = self
            
    def addWeightOut(self,w):
        self.weights_out.append(w)
        w.node_from = self
            
        
class MLP:
    
    def __init__(self,layout,actfun,divfun):
        self.num_layers = len(layout)-1
        self.network = []
        self.weights = []
        self.input_layer = []
        self.output_layer = []
        blank = lambda x:x
        
        
        for _ in range(layout[0]):
            self.input_layer.append(Node(blank,blank))
        self.network.append(self.input_layer)
        
        for i in range(1,self.num_layers):
            new_layer = []
            for _ in range(layout[i]):
                new_node = Node(actfun,divfun)
                new_layer.append(new_node)
                for n in self.network[i-1]:
                    new_weight = Weight()
                    new_weight.weight = (2.0* random.random())-1.0
                    new_node.addWeightIn(new_weight)
                    n.addWeightOut(new_weight)
                    self.weights.append(new_weight)
                self.network.append(new_layer)       
        
        self.output_layer = []
        for _ in range(layout[self.num_layers]):
            new_node = Node(blank,blank)
            self.output_layer.append(new_node)
            for n in self.network[self.num_layers-1]:
                new_weight = Weight()
                new_weight.weight = (2.0* random.random())-1.0
                new_node.addWeightIn(new_weight)
                n.addWeightOut(new_weight)
                self.weights.append(new_weight)
            self.network.append(self.output_layer)
        
    def train(self,X,y):
        err_sum = 0.0
        for i in range(len(X)):
            self.input_layer[i].output = X[i]
            
        for i in range(1,len(self.network)):
            for n in self.network[i]:
                n.feedfoward()
                
        for i in range(len(y)):
            err = self.output_layer[i].output - y[i]
            self.output_layer[i].delta = err
            err_sum += err*err
        
        for i in reversed(range(1,self.num_layers-1)):
            for n in self.network[i]:
                n.calcDelta()
        
        for w in self.weights:
            w.update()
            
        return err_sum
        
        


def main(args):
    actfun = lambda x: x*(x>0)
    divfun = lambda x: 1.0*(x>0)
    mlp = MLP([3,4,1],actfun,divfun)
    X = [[ 1, 0, 1 ],
        [ 0, 1, 1 ],
        [ 0, 0, 1 ],
        [ 1, 1, 1 ]]
    y = [ [1], [1], [0], [0]]
    
    for it in range(61):
        err = 0.0
        for i in range(len(X)):
            err += mlp.train(X[i],y[i])
        if(it % 10 == 0):
            print(it,err)    
    return 0

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
