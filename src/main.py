from rich import print
from rich import prompt
from rich.panel import Panel
from textual.app import App
from textual.containers import VerticalScroll
from textual.widgets import Button, Header, Footer, Static

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


def do_slep(numbieSlepSecs = 5):

    time.sleep(numbieSlepSecs)


class LogScroll(VerticalScroll):
    def __init__(self):
        super().__init__(id="static1")
    
    def append(self, text: str):
        for line in text.splitlines():
            self.mount(Static(f"[cyan]{line}"))
        self.scroll_end(animate=False)

class CivSculptorSim(App):
    CSS_PATH = "grid.tcss"

    def __init__(self):
        super().__init__()
        self.sim = civ_module.SimulationApi(123456, "Testonia")
        self.header = Header("CivSculptor Sim")
        self.log_widget = LogScroll()
        from textual.containers import Grid
        
        self.grid = Grid(classes="button-grid")

        self.step1Button = Button("Step 1", classes="button")
        self.step3Button = Button("Step 3", classes="button")
        self.generate3CivsButton = Button("Gen 3 Civ", classes="button", id="genCivsButton")
        self.exitButton = Button("Exit", classes="button", id="exitButton")


    def compose(self):
        yield self.header
        yield self.log_widget
        yield self.step1Button
        yield self.step3Button
        yield self.generate3CivsButton
        yield self.exitButton
        yield Footer()


    def on_mount(self):

        self.set_interval(0.05, self.poll_logs)

        grid = self.grid

        # grid.set_gap(1, 0)

        # grid.add_column("col1")


    def styleStepButtons(self, button):
        

        button.styles.background = "cyan"

        button.styles.color = "purple"

        button.styles.text_style = "underline"
    


    def styleCivButtons(self, button):

        button.styles.background = "purple"

        button.styles.color = "cyan"

        button.styles.text_style = "italic"


    def poll_logs(self):
        out = self.sim.poll_log()
        if out:
            self.log_widget.append(out)

    def on_button_pressed(self, event):

        if event.button.label == "Gen 3 Civ":

            self.sim.generate3Civs()

        elif event.button.label == "Step 1":

            self.log_widget.append("Starting sim!!!")

            self.sim.startSimulationAsync(1)

        elif event.button.label == "Step 3":

            self.log_widget.append("Button clicked!")

            self.sim.startSimulationAsync(3)

        else:

            self.log_widget.append("Exiting Program")

            self.exit("Bye ;-; we'll miss you!")



def main():


    # console.print(Panel("[italic cyan]Get Ready", title = "[italic cyan]Welcome to [bold purple]civsim_tui.py[/italic cyan]"), justify="center")


    # # with console.status("Sleeping...", spinner="bouncingBar"):

    # #     do_slep()

    # sim = civ_module.SimulationApi(123456, "Testonia")

    # if prompt.Confirm.ask("[italic cyan] start sim?"):

    #     with console.screen():
            

    #         sim.startSimulationAsync(3)
            


    #         do_slep()

    #         sim.startSimulationAsync(3)


    #         do_slep()
    app = CivSculptorSim()
    app.run()

if __name__ == "__main__":
    main()