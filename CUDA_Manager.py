from cuda import cuda, nvrtc
import os
from CUDA_Command import CUDA_Command


class CUDA_Manager:
    def setup_cpp_command_dictionary(self):
        """
        Prepares a dictionary of all cpp functions in /CppCode as text in a dictionary
        """
        for function_file_name in os.listdir("./CppCode/"):
            with open("./CppCode/" + function_file_name, "r") as file:
                self.cpp_commands[function_file_name[:-4]] = CUDA_Command(file.read())

    def __init__(self):
        self.cpp_commands = dict()
        self.setup_cpp_command_dictionary()

    def execute_command(self, command_name: str):
        try:
            print(self.cpp_commands[command_name])
        except KeyError:
            raise Exception(f"CUDA Command {command_name} does not exist")
