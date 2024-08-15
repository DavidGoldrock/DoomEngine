import os

for filename in os.listdir("../cpp_code/entities/"):
    with open("../cpp_code/entities/" + filename, "r") as file:
        fileContent = file.read()
        print(fileContent)
    try:
        with open("../cpp_code/entities/" + filename, "w") as file:
                content = f"#include \"../headers/{filename.split('.')[0]+'.h'}\"\n" + "\n".join(fileContent.split("\n")[1:])
                file.write(content)
    except:
         pass
    