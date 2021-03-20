import json
import os
import subprocess


def main():
    config = open("configuration.json", "r")
    runnables = json.loads(config.read())
    config.close()

    current = os.getcwd()
    for runnable in runnables:
        print(runnable["name"])
        os.chdir(runnable["path"])
        subprocess.run(runnable["runnable"], shell=True, check=True, capture_output=False)
        os.chdir(current)


if __name__ == "__main__":
    main()
