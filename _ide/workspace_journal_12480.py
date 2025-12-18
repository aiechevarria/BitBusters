# 2025-12-13T22:56:02.640982200
import vitis

client = vitis.create_client()
client.set_workspace(path="BitBusters-Basys")

comp = client.get_component(name="game")
comp.build()

vitis.dispose()

