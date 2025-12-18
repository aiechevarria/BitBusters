# 2025-12-12T00:51:50.049561700
import vitis

client = vitis.create_client()
client.set_workspace(path="BitBusters-Basys")

comp = client.get_component(name="game")
comp.build()

comp.build()

