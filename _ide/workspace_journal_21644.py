# 2025-12-12T00:16:47.535982
import vitis

client = vitis.create_client()
client.set_workspace(path="BitBusters-Basys")

comp = client.get_component(name="game")
comp.build()

comp.build()

comp.build()

comp.build()

vitis.dispose()

