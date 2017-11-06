#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <fstream>
#include <random>
#include <sstream>

int rnd_val(unsigned int a, unsigned int b) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(a, b);

    return dist6(rng);
}
class network {

public: unsigned int size = 0;
    std::vector <int> neurons;
    std::vector <double> biases;
    std::vector < std::vector <double> > weights;

    void init_random(unsigned int a) {
        size = a;
        init_random_neurons();
        init_random_biases();
        init_random_weights();
    }
    void init_input(unsigned int a, std::vector< std::vector <int> > &memory, std::vector<int> &input_binary) {
        size = a;
        init_neurons(input_binary);
        init_random_biases();
        init_weights(memory);
    }
    void init_weights(std::vector< std::vector <int> > &mem) {
        auto img_size = static_cast<unsigned int> (mem[0].size());
        weights.resize(img_size);
        for (int i = 0; i < img_size; i++) {
            weights[i].resize(img_size);
        }

        for(std::vector<int> &a : mem) {
            std::vector<int> v;
            v.resize(img_size);

            for (int i = 0; i < img_size; i++) {
                v[i] = a[i];
            }
            for (int i = 0; i < img_size; i++) {
                for (int j = 0; j < img_size; j++) {
                    weights[i][j] += v[i] * v[j];
                }
                weights[i][i] = 0;
            }
        }
    }
    void init_neurons(std::vector<int> &a) {
        neurons.resize(a.size());
        for (int i = 0; i < a.size(); i++) {
            neurons[i] = a[i];
        }
    }
    double energy() {
        double energy = 0;
        for(int i = 0; i < weights.size(); i++) {
            for (int j = 0; j < weights.size(); j++) {
                energy += -0.5*weights[i][j]*neurons[i]*neurons[j];
            }
            energy += biases[i]*neurons[i];
        }
        return energy;
    }
    bool update() {
        int rand_n = rnd_val(0, size-1);
        double t_weight = 0.0;
        for (int i = 0; i < weights[rand_n].size(); i++) {
            t_weight += weights[rand_n][i]*neurons[i];
        }
        if (t_weight > biases[rand_n]) {
            neurons[rand_n] = 1;
            return true;
        }
        neurons[rand_n] = -1;
        return false;
    }
    bool converged() {
        for (int n = 0; n < neurons.size(); n++) {
            double t_weight = 0.0;
            for (int i = 0; i < weights[n].size(); i++) {
                t_weight += weights[n][i]*neurons[i];
            }
            if (t_weight > biases[n] && neurons[n] != 1) {
                return false;
            }
            if (t_weight <= biases[n] && neurons[n] != -1) {
                return false;
            }
        }
        return true;
    }
private: void init_random_neurons() {
        neurons.resize(size);
        for (auto &neuron : neurons) {
            neuron = static_cast<int> (std::pow(-1, rnd_val(1,6)));
        }
        cout_vector(neurons);
    }
    void init_random_weights() {
        weights.resize(size);
        for(int i = 0; i < size; i++){
            weights[i].resize(size);
        }
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++) {
                if (i == j) {
                    weights[i][j] = 0.0;
                }
                else {
                    auto rnd_weight = std::pow(-1.0, rnd_val(1,6))*(rnd_val(0, 1000))/1000.0;
                    weights[i][j] = rnd_weight;
                    weights[j][i] = rnd_weight;
                }
            }
        }
        cout_weights();
    }
    void init_random_biases() {
        biases.resize(size);
        for (auto &bias : biases) {
            bias = std::pow(-1.0, rnd_val(1, 6))*(rnd_val(0, 1000))/1000.0;
        }
    }

public: void cout_vector(std::vector <int> &a) {
        std::cout << std::endl;
        for (auto &item : a) {
            std::cout << item << std::endl;
        }
        std::cout << "\n\n\n";
    }
    void cout_weights() {
        std::cout << "\nWeights:" << std::endl;
        for (auto &weight : weights) {
            for (int j = 0; j < weights.size(); ++j) {
                std::cout << weight[j] << "\t\t";
            }
            std::cout << std::endl;
        }
        std::cout << "\n\n\n";
    }
};
std::vector<std::vector<int>> convert_strings_to_2d_vector(std::vector<std::string> &a) {
    std::vector<std::vector<int>> bin_vec;
    bin_vec.resize(a.size());
    for (int i  = 0; i < a.size(); i++) {
        for (char &b : a[i]) {
            if (b == '0') {
                bin_vec[i].push_back(-1);
            } else {
                bin_vec[i].push_back(1);
            }
        }
    }
    return bin_vec;
}
std::vector<int> convert_string_to_vector(std::string &a) {
    std::vector<int> input;
    for (char &b : a) {
        if (b == '0') {
            input.push_back(-1);
        }
        else {
            input.push_back(1);
        }
    }
    return input;
}

void txtout_value(std::ofstream &txtout, double val) {
    txtout << val <<'\n';
}
void txtout_vector(std::ofstream &txtout, std::vector <int> a) {
    for (int &neuron : a) {
        if (neuron == -1) {
            txtout << 0;
        }
        else {
            txtout << 1;
        }
    }
    txtout << std::endl;
}
std::vector < std::vector <int> > gen_input_vector(std::ifstream &in_stream){
    std::vector <std::string> memory_str_vec;
    std::string memory_face_str = "0000000000000100010000000000000000000000000010000000000000000001110000001000100001000001101000000001";
    memory_str_vec.push_back(memory_face_str);
    std::string memory_tree_str = "0001111000000111100000001100000000110000001111111000001100100000110000000011000000001100000000110000";
    memory_str_vec.push_back(memory_tree_str);

    std::string line;
    while (std::getline(in_stream, line)) {
        memory_str_vec.push_back(line);
    }

    auto a = convert_strings_to_2d_vector(memory_str_vec);
    return a;
}

int main() {
    std::ofstream txtoutput;
    txtoutput.open ("neurons.txt");

    std::ifstream mem_file_stream ("memories.txt");
    std::ifstream infile ("memories_corr.txt");
    unsigned int size = 100;
    network net;

    auto memories = gen_input_vector(mem_file_stream);
    std::string input_str = "0001111100000011000000001100000000110000001111110000011100100000110000000011000000001100000001100100";
    auto input = convert_string_to_vector(input_str);



    for (int run = 0; run < 10; run++) {
        net.init_input(size, memories, input);
        txtout_vector(txtoutput, net.neurons);
        net.cout_vector(net.neurons);
        while (!net.converged()) {
            net.update();
            txtout_vector(txtoutput, net.neurons);
        }
        if (run < 10-1) {txtoutput << "\n";}
    }
    txtoutput.close();
    return 0;
}