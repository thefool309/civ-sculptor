from rich import print
from rich import prompt
from rich.panel import Panel
from textual.app import App
from textual.containers import VerticalScroll
from textual.widgets import RichLog
from textual.widgets import Button, Header, Footer, Static
from textual.binding import Binding
from rich.text import Text

import os
import sys


script_dir = os.path.dirname(os.path.abspath(__file__))
build_dir = os.path.join(script_dir, "..", "build")
build_dir = os.path.abspath(build_dir)

sys.path.append(build_dir)

import civ_module

from rich import pretty
import time
from rich.console import Console
console = Console()
pretty.install()


def do_slep(numbieSlepSecs = 5):

    time.sleep(numbieSlepSecs)


class LogScroll(RichLog):
    def __init__(self):
        super().__init__(id="static1")
    
    def log(self, text: str):
        for line in text.splitlines():
            self.write(Text(f"{line}", style="cyan"))

class CivSculptorSim(App):
    CSS_PATH = "main.tcss"


    BINDINGS = [
        Binding(key="q", action="quit", description="Quit the app"),
    ]
    def __init__(self, rng_seed, name):
        super().__init__()
        self.sim = civ_module.SimulationApi(rng_seed, name)
        self.header = Header("CivSculptor Sim")
        self.log_widget = LogScroll()
        from textual.containers import Grid
        
        self.grid = Grid(classes="button-grid")

        self.step1Button = Button("Step 1", classes="button")
        self.step3Button = Button("Step 3", classes="button")
        self.generate3CivsButton = Button("Gen 3 Civ", classes="button", id="gen-civs-button3")
        self.generate5CivsButton = Button("Gen 5 Civ", classes="button", id="gen-civs-button5")
        self.generate10CivsButton = Button("Gen 10 Civ", classes="button", id="gen-civs-button10")
        self.exitButton = Button("Exit", classes="button", id="exitButton")
        self.nonsenseButton = Button("Nonsense", classes="button", id="nonsense-button")


    def compose(self):
        yield self.header
        yield self.log_widget
        yield self.step1Button
        yield self.step3Button
        yield self.generate3CivsButton
        yield self.generate5CivsButton
        yield self.generate10CivsButton
        yield self.exitButton
        yield Footer()


    def on_mount(self):
        self.set_interval(0.05, self.poll_logs)
        grid = self.grid

        # grid.set_gap(1, 0)

        # grid.add_column("col1")

    def poll_logs(self):
        out = self.sim.poll_log()
        if out:
            self.log_widget.log(out)

    def on_button_pressed(self, event):
        if event.button.label == "Gen 3 Civ":
            self.sim.generate3Civs()
        elif event.button.label == "Gen 5 Civ":
            self.sim.generate5Civs()
        elif event.button.label == "Gen 10 Civ":
            self.sim.generate10Civs()
        elif event.button.label == "Step 1":
            self.log_widget.log("Starting sim!!!")
            self.sim.startSimulationAsync(1)
        elif event.button.label == "Step 3":
            self.log_widget.log("Starting sim!!!")
            self.sim.startSimulationAsync(3)
        elif event.button.label == "Nonsense":
            self.log_widget.log("UwU OwO :3 >^w^<")
        else:
            self.log_widget.log("Exiting Program")
            self.exit("Bye ;-; we'll miss you!")



def main():
    console.print(Panel("[italic bold underline cyan]Welcome to civ-sculptor Simulation"), justify="center")
    rng_seed = prompt.IntPrompt.ask("World rng_seed(0 for default)")
    name = prompt.Prompt.ask("World Name (Leave blank for default)")
    
    if prompt.Confirm.ask("[italic cyan] start sim?"):
        if rng_seed > 0 and name:
            app = CivSculptorSim(rng_seed, name)
        else:
            app = CivSculptorSim(123456, "Testonia")
        app.run()
    
    console.print(Panel("[italic bold red] goodbye >:3"), justify="center")

if __name__ == "__main__":
    main()