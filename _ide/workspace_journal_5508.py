# 2025-12-12T14:59:51.237168400
import vitis

client = vitis.create_client()
client.set_workspace(path="BitBusters-Basys")

comp = client.get_component(name="game")
comp.build()

vitis.dispose()

