# 2025-12-15T23:18:52.429093700
import vitis

client = vitis.create_client()
client.set_workspace(path="BitBusters-Basys")

comp = client.get_component(name="game")
comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

vitis.dispose()

