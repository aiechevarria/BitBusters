# 2025-12-12T15:11:31.556072200
import vitis

client = vitis.create_client()
client.set_workspace(path="BitBusters-Basys")

comp = client.get_component(name="game")
comp.build()

comp.build()

vitis.dispose()

