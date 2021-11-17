#!/bin/python3

import os
from common import run_command

if __name__ == "__main__":
    # make sure build folder exists
    path = os.path.join(os.getcwd(), "dist", "Emscripten")

    run_command(['npx', 'http-server', path])



