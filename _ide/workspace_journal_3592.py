# 2025-12-12T00:32:39.050840300
import vitis

client = vitis.create_client()
client.set_workspace(path="BitBusters-Basys")

comp = client.get_component(name="game")
comp.build()

status = comp.clean()

comp.build()

comp.build()

comp.build()

vitis.dispose()

