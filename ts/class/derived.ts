
import { print } from './utils'
import { Base } from './base'

export class Derived extends Base {
  constructor() {
    super()
    print('Derived constructor')
  }
}


