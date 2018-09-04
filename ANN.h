
/*
 * Copyright (c) 2012 Karl N. Redgate
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <unistd.h>
#include <string>

#include "Graph.h"

#ifndef _NEURALNET_H_
#define _NEURALNET_H_

/**
 */
class Neuron : public Vertex {
public:
    Neuron();
    virtual ~Neuron();
};

/**
 * dendrite is incoming, axon would be outgoing.
 * But an axon output should go to multiple and there is a single axon
 */
class Dendrite : public Edge {
public:
    Dendrite();
    Dendrite( Neuron * );
    virtual ~Dendrite();
};

/**
 */
class Layer : public Graph {
public:
    bool connect( Layer * );
    Layer();
    Layer( int );
    virtual ~Layer();
};

/**
 */
class Perceptron {
private:
    Layer *in;
    Layer *hidden;
    Layer *out;
public:
    Perceptron();
    virtual ~Perceptron();
};



/**
 * https://en.wikipedia.org/wiki/Learning_rule
 *
 * Learning rule or Learning process is a method or a mathematical
 * logic which improves the artificial neural network's performance
 * and usually this rule is applied repeatedly over the network.
 * It is done by updating the weights and bias levels of a network
 * when a network is simulated in a specific data environment.
 * A learning rule may accept existing condition (weights and bias)
 * of the network and will compare the expected result and
 * actual result of the network to give new and improved values
 * for weights and bias.
 * Depending on the complexity of actual model, which is being
 * simulated, the learning rule of the network can be as simple as
 * an XOR gate or Mean Squared Error or it can be the result of
 * multiple differential equations. The learning rule is one of the
 * factors which decides how fast or how accurate the artificial
 * network can be developed. Depending upon the process to develop
 * the network there are three main models of machine learning:
 *
 *  * Unsupervised learning
 *  * Supervised learning
 *  * Reinforcement learning
 */
class LearningRule {
};

/**
 */
class ANN {
};

/**
 */
class FeedForwardNet : public ANN {
};

/**
 * https://en.wikipedia.org/wiki/Time_delay_neural_network
 */
class TimeDelayNet : public FeedForwardNet {
};

/**
 * https://en.wikipedia.org/wiki/Time_delay_neural_network
 * They are also known as shift invariant or space invariant
 * artificial neural networks (SIANN), based on their
 * shared-weights architecture and translation invariance
 * characteristics.
 */
class ConvolutionalNet : public FeedForwardNet {
};

/**
 */
class RecurrentNet : public ANN {
};

/**
 */
class HopfieldNet : public RecurrentNet {
};

/**
 */
class BAMNet : public HopfieldNet {
};

/**
 */
class JordanNet : public RecurrentNet {
};

/**
 */
class ElmanNet : public RecurrentNet {
};

/**
 */
class NeuralHistoryCompressor {
    // unsupervised stack of RNN
};

/**
 */
class LongShortTermMemoryNet : public RecurrentNet {
};

/**
 * https://en.wikipedia.org/wiki/Reservoir_computing
 *
 * The reservoir consists of a collection of recurrently connected
 * units. The connectivity structure is usually random, and the units
 * are usually non-linear. The overall dynamics of the reservoir are
 * driven by the input, and also affected by the past. A rich collection
 * of dynamical input-output mapping is a crucial advantage over time
 * delay neural networks.
 */
class Reservoir : public RecurrentNet {
};

/**
 * https://en.wikipedia.org/wiki/Spiking_neural_network
 *
 * Spiking neural networks (SNNs) are artificial neural network
 * models that more closely mimic natural neural networks.
 * In addition to neuronal and synaptic state, SNNs also
 * incorporate the concept of time into their operating model.
 * The idea is that neurons in the SNN do not fire at each
 * propagation cycle (as it happens with typical multi-layer
 * perceptron networks), but rather fire only when a membrane
 * potential - an intrinsic quality of the neuron related to its
 * membrane electrical charge - reaches a specific value.
 * When a neuron fires, it generates a signal which travels
 * to other neurons which, in turn, increase or decrease their
 * potentials in accordance with this signal.
 */
class SpikingNet : public Reservoir {
};

/**
 * https://en.wikipedia.org/wiki/Echo_state_network
 * http://aureservoir.sourceforge.net/
 */
class EchoStateNet : public Reservoir {
};

/**
 * https://en.wikipedia.org/wiki/Liquid_state_machine
 *
 * LSMs have been put forward as a way to explain the operation of
 * brains. LSMs are argued to be an improvement over the theory of
 * artificial neural networks because:
 *
 * 1. Circuits are not hard coded to perform a specific task.
 * 2. Continuous time inputs are handled "naturally".
 * 3. Computations on various time scales can be done using the
 *    same network.
 * 4. The same network can perform multiple computations.
 *
 * Criticisms of LSMs as used in computational neuroscience are that
 * 1. LSMs don't actually explain how the brain functions. At best
 *    they can replicate some parts of brain functionality.
 * 2. There is no guaranteed way to dissect a working network and
 *    figure out how or what computations are being performed.
 * 3. Very little control over the process.
 */
class LiquidStateMachine : public SpikingNet {
};

/**
 */
class ContinuousTimeNet : public RecurrentNet {
};

/**
 */
class HierarchicalNet : public RecurrentNet {
};

/**
 */
class NeuralTuringMachine : public RecurrentNet {
};

/**
 */
class DifferentiableNeuralComputer : public NeuralTuringMachine {
};

/*
 * Learning?
 * https://en.wikipedia.org/wiki/Linear_regression
 * https://en.wikipedia.org/wiki/Ridge_regression
 * https://en.wikipedia.org/wiki/Linear_discriminant_analysis
 */

#endif

/* vim: set autoindent expandtab sw=4 : */
