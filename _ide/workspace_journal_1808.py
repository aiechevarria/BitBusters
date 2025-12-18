# 2025-12-10T15:24:53.501868500
import vitis

client = vitis.create_client()
client.set_workspace(path="BitBusters-Basys")

platform = client.get_component(name="platform")
status = platform.build()

comp = client.get_component(name="game")
comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = comp.clean()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = comp.clean()

status = platform.build()

comp.build()

status = comp.clean()

status = platform.build()

comp.build()

status = comp.clean()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

vitis.dispose()

