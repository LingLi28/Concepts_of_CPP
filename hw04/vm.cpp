#include "vm.h"

#include <iostream>
#include <limits>

#include "util.h"


namespace vm {


vm_state create_vm(bool debug) {
    vm_state state;

    // enable vm debugging
    state.debug = debug;


    register_instruction(state, "PRINT", [](vm_state& vmstate, const item_t /*arg*/) {
        std::cout << vmstate.stack.top() << std::endl;
        return true;
    });

    register_instruction(state, "LOAD_CONST", [](vm_state& vmstate, const item_t number){
        vmstate.stack.push(number);
        return true;
    });

    register_instruction(state, "EXIT", [](vm_state& vmstate, const item_t /*arg*/){
        // TODO: stop running
        if (vmstate.stack.empty()){
            throw vm_stackfail{"Not enough stack items!"};
        }

        return false;
        
    });

    register_instruction(state, "POP", [](vm_state& vmstate, const item_t /*arg*/){
        if (!vmstate.stack.empty()){
            vmstate.stack.pop();
            return true;
        }
        else
            throw vm_stackfail{"Not enough stack items!"};
    });

    register_instruction(state, "ADD", [](vm_state& vmstate, const item_t /*arg*/){
     if (!vmstate.stack.empty()){
        item_t TOS = vmstate.stack.top();
        vmstate.stack.pop();
            if (!vmstate.stack.empty()){
                item_t TOS1 = vmstate.stack.top();
                vmstate.stack.pop();
                vmstate.stack.push(TOS1 + TOS);
                return true;
            } 
            else
                throw vm_stackfail{"Not enough stack items!"};
        } 
        else
            throw vm_stackfail{"Not enough stack items!"};
        

    });

    register_instruction(state, "DIV", [](vm_state& vmstate, const item_t /*arg*/){
        if (!vmstate.stack.empty()){

            item_t TOS = vmstate.stack.top();
            vmstate.stack.pop();

            if (!vmstate.stack.empty()){
                item_t TOS1 = vmstate.stack.top();
                vmstate.stack.pop();
                 if (TOS == 0){
                    throw div_by_zero{"Divided by zero!"};
                 }
            
                else {
                    vmstate.stack.push(TOS1 / TOS);
                    return true;
                }
            }
           
            else
                throw vm_stackfail{"Not enough stack items!"};
        }         
        else
            throw vm_stackfail{"Not enough stack items!"};

    });

    register_instruction(state, "EQ", [](vm_state& vmstate, const item_t /*arg*/){
       if (!vmstate.stack.empty()){

            item_t TOS = vmstate.stack.top();
            vmstate.stack.pop();

            if (!vmstate.stack.empty()){
                item_t TOS1 = vmstate.stack.top();
                vmstate.stack.pop();
                if (TOS1 == TOS){
                    vmstate.stack.push(1);
                }
                else{
                    vmstate.stack.push(0);
                }
                return true;
                
            }
           
            else
                throw vm_stackfail{"Not enough stack items!"};
        }         
        else
            throw vm_stackfail{"Not enough stack items!"};

    });

    register_instruction(state, "NEQ", [](vm_state& vmstate, const item_t /*arg*/){
        if (!vmstate.stack.empty()){

            item_t TOS = vmstate.stack.top();
            vmstate.stack.pop();

            if (!vmstate.stack.empty()){
                item_t TOS1 = vmstate.stack.top();
                vmstate.stack.pop();
                if (TOS1 == TOS){
                    vmstate.stack.push(0);
                }
                else{
                    vmstate.stack.push(1);
                }
                return true;
                
            }
           
            else
                throw vm_stackfail{"Not enough stack items!"};
        }         
        else
            throw vm_stackfail{"Not enough stack items!"};
    });

    register_instruction(state, "DUP", [](vm_state& vmstate, const item_t ){
            if (vmstate.stack.empty())
                throw vm_stackfail{"Not enough stack items!"};

            item_t TOS = vmstate.stack.top();
            vmstate.stack.push(TOS);

            return true;
        });


    register_instruction(state, "JMP", [](vm_state& vmstate, const item_t addr){
        size_t range = vmstate.code.size()-1;
        if (addr > range)
            throw vm_segfault{"Address does not exist!"};
        else
            vmstate.pc = addr;

        return true;
    });

    register_instruction(state, "JMPZ", [](vm_state& vmstate, const item_t addr){
        size_t range = vmstate.code.size()-1;
        if (vmstate.stack.empty()){
            throw vm_stackfail{"Not enough stack items!"};
        }

        if (addr > range)
            throw vm_segfault{"Address does not exist!"};

        if (!vmstate.stack.empty()){
            item_t TOS = vmstate.stack.top();
            vmstate.stack.pop();
            if (TOS == 0)
                vmstate.pc = addr;
             return true;
        } 
            
        else
            throw vm_stackfail{"Not enough stack items!"};
       
    });

    register_instruction(state, "WRITE", [](vm_state& vmstate, const item_t /*arg*/){
        if (vmstate.stack.empty()) 
            throw vm_stackfail{"Not enough stack items!"};

        item_t TOS = vmstate.stack.top();
        vmstate.out << TOS;
        return true;
    });

    register_instruction(state, "WRITE_CHAR", [](vm_state& vmstate, const item_t /*arg*/){
        if (vmstate.stack.empty()) 
            throw vm_stackfail{"Not enough stack items!"};

        item_t TOS = vmstate.stack.top();
        vmstate.out << static_cast<char>(TOS);
        return true;

    });

    // TODO create instructions

    return state;
}


void register_instruction(vm_state& state, std::string_view name,
                          const op_action_t& action) {
    size_t op_id = state.next_op_id;

    state.instruction_ids.insert(std::make_pair(name, op_id));
    state.instruction_names.insert(std::make_pair(op_id, name));
    state.instruction_actions.insert(std::make_pair(op_id, action));

    state.next_op_id += 1;

    // TODO make instruction available to vm
}


code_t assemble(const vm_state& state, std::string_view input_program) {
    code_t code;

    // convert each line separately
    for (auto& line : util::split(input_program, '\n')) {

        auto line_words = util::split(line, ' ');

        // only support instruction and one argument
        if (line_words.size() >= 3) {
            throw invalid_instruction{std::string{"more than one instruction argument: "} + line};
        }

        // look up instruction id
        auto& op_name = line_words[0];
        auto find_op_id = state.instruction_ids.find(op_name);
        if (find_op_id == std::end(state.instruction_ids)) {
            throw invalid_instruction{std::string{"unknown instruction: "} + op_name};
        }
        op_id_t op_id = find_op_id->second;

        // parse the argument
        item_t argument{0};
        if (line_words.size() == 2) {
            argument = std::stoll(line_words[1]);
        }

        // and save the instruction to the code store
        code.emplace_back(op_id, argument);
    }

    return code;
}


std::tuple<item_t, std::string> run(vm_state& vm, const code_t& code) {
    vm.code = code;
    // to help you debugging the code!
    if (vm.debug) {
        std::cout << "=== running vm ======================" << std::endl;
        std::cout << "disassembly of run code:" << std::endl;
        for (const auto &[op_id, arg] : code) {
            if (not vm.instruction_names.contains(op_id)) {
                std::cout << "could not disassemble - op_id unknown..." << std::endl;
                std::cout << "turning off debug mode." << std::endl;
                vm.debug = false;
                break;
            }
            std::cout << vm.instruction_names[op_id] << " " << arg << std::endl;
        }
        std::cout << "=== end of disassembly" << std::endl << std::endl;
    }

    // execution loop for the machine
    while (true) {

        auto& [op_id, arg] = code[vm.pc];

        if (vm.debug) {
            std::cout << "-- exec " << vm.instruction_names[op_id] << " arg=" << arg << " at pc=" << vm.pc << std::endl;
        }

        // increase the program counter here so its value can be overwritten
        // by the instruction when it executes!
        vm.pc += 1;


        // TODO execute instruction and stop if the action returns false.
        bool result = vm.instruction_actions[op_id](vm, arg);

        if (result == false)
            break;

    }

    if (vm.stack.empty())
        throw vm_stackfail{"Not enough stack items!"};

    std::tuple<item_t, std::string> result(vm.stack.top(), vm.out.str());

    return result; // TODO: return tuple(exit value, output text)
}


} // namespace vm
