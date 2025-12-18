# 2025-12-09T15:27:29.708536500
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

