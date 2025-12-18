# 2025-12-10T14:44:10.375732700
import vitis

client = vitis.create_client()
client.set_workspace(path="BitBusters")

platform = client.get_component(name="platform")
status = platform.build()

comp = client.get_component(name="game")
comp.build()

vitis.dispose()

vitis.dispose()

