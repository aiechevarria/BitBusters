# 2025-12-07T20:09:38.747928800
import vitis

client = vitis.create_client()
client.set_workspace(path="BitBusters")

platform = client.get_component(name="platform")
status = platform.build()

comp = client.get_component(name="game")
comp.build()

status = platform.build()

comp.build()

vitis.dispose()

