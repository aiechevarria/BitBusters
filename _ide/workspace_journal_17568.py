# 2025-12-07T20:12:34.379327700
import vitis

client = vitis.create_client()
client.set_workspace(path="BitBusters")

comp = client.get_component(name="game")
status = comp.clean()

platform = client.get_component(name="platform")
status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

vitis.dispose()

