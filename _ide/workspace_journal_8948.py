# 2025-12-09T15:46:24.881184300
import vitis

client = vitis.create_client()
client.set_workspace(path="BitBusters")

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

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

vitis.dispose()

