from rich import print
from rich import prompt

from rich.panel import Panel

import os
import sys

script_dir = os.path.dirname(os.path.abspath(__file__))
build_dir = os.path.join(script_dir, "..", "build", "Debug")
build_dir = os.path.abspath(build_dir)

sys.path.append(build_dir)

import civ_module

from rich import pretty

import time


from rich.console import Console

console = Console()

pretty.install()

def do_slep():

    time.sleep(5)


def main():

    a = 1
    b = 1

    

    console.print(Panel("[italic cyan]Python binding test[/] [bold green]Success[/] [italic purple]the result of our c++ function is[/italic purple] [bold red]" + str(civ_module.add(a, b))), justify="center")

    console.print(Panel("[italic cyan]Get Ready", title = "[italic cyan]Welcome to [bold purple]civsim_tui.py[/italic cyan]"), justify="center")

    # with console.status("Sleeping...", spinner="bouncingBar"):
    #     do_slep()
    
    if prompt.Confirm.ask("[italic cyan] start sim?"):
        with console.screen():
            civ_module.startSimulation()

            do_slep()

if __name__ == "__main__":
    main()