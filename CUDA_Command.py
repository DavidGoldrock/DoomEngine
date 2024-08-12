from cuda import cuda, nvrtc


class CUDA_Command:

    def __init__(self, cpp_string: str):
        self.cpp_string = cpp_string

        # Create the program using nvrtc
        # TODO: Get a new hard drive so you can install nvidia CUDA
        err, self.prog = nvrtc.nvrtcCreateProgram(str.encode(cpp_string), (cpp_string + ".cu").encode(), 0, [], [])
        self.ASSERT_DRV(err)

    def ASSERT_DRV(self, err):
        """
        :param err: error from a CUDA command
        :return: raises an error based on where the error occurred
        """
        if isinstance(err, cuda.CUresult):
            if err != cuda.CUresult.CUDA_SUCCESS:
                raise RuntimeError(f"Cuda Error: {err}\nCPP Code origin:\n{self.cpp_string}")
        elif isinstance(err, nvrtc.nvrtcResult):
            if err != nvrtc.nvrtcResult.NVRTC_SUCCESS:
                raise RuntimeError(f"Nvrtc Error: {err}\nCPP Code origin:\n{self.cpp_string}")
        else:
            raise RuntimeError(f"Unknown error type: {err}\nCPP Code origin:\n{self.cpp_string}")

    def __str__(self):
        tab = "    "
        tabbed_string = f"\n{tab}{tab}" + self.cpp_string.replace("\n", f"\n{tab}{tab}")
        return f"""
CUDA Command:
{tab}string:{tabbed_string}
"""

    __repr__ = __str__
